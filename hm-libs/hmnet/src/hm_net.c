/*
 * hm_net.c
 *
 * This file implements net, used for net io objects management.
 *
 * Copyright(c) by HiMickey, 2010~2014
 * Author:
*/

#include <string.h>
#include "hm_errno.h"
#include "hm_debug.h"
#include "hm_net.h"
#include "hm_netproto.h"
#include "hm_scheduler.h"

struct _JNet
{
    int			ref_count;
    int			killed;     	/* state */

    HMList		*io_list;  		/* net-io object list */
    JMutex		*lock;
	JScheduler	*scheduler;		/* IO scheduler */

    JIOInit		on_init;
    JIOFin		on_fin;

};


static __inline__ void
hm_net_init(JNet *self, int loops)
{
    atomic_set(&self->ref_count, 1);
    self->killed = 0;
    self->io_list = NULL;
    self->lock = hm_mutex_new();
    self->scheduler = hm_scheduler_new(loops);

    self->on_init = NULL;
    self->on_fin = NULL;
}


__export JNet *
hm_net_new(int loops)
{
    JNet *net;

    net = hm_new0(JNet, 1);
    hm_net_init(net, loops);

    return net;
}

static __inline__ void
hm_net_free(JNet *net)
{
    BUG_ON(!net->killed);
    BUG_ON(net->io_list);
    BUG_ON(net->io_list);

    hm_mutex_free(net->lock);
    hm_del(net, JNet, 1);
}


__export JNet *
hm_net_ref(JNet *net)
{
    J_ASSERT(net != NULL && 
        atomic_get(&net->ref_count) > 0);

    atomic_inc(&net->ref_count);
    return net;
}


__export void
hm_net_unref(JNet *net)
{
    J_ASSERT(net != NULL && 
        atomic_get(&net->ref_count) > 0);

    if (atomic_dec_and_test_zero(&net->ref_count))
    {
        hm_net_free(net);
    }   
}


static __inline__ void
hm_net_kill(JNet *net)
{
	//BUG();
}


__export void
hm_net_release(JNet *net)
{//TODO:
    J_ASSERT(net != NULL);

    hm_net_kill(net);
    hm_net_unref(net);
}


__export void 
hm_net_set_funcs(JNet *net, JIOInit init, JIOFin fin)
{
    J_ASSERT(net != NULL);

    net->on_init = init;
    net->on_fin = fin;
}


static __inline__ int
__hm_net_kill_io(JNet *net, JNetIO *net_io, void *init_data, 
	int notify, int err)
{
    HMList *list;

    if (net->killed)
        return 0;

    list = hm_list_find(net->io_list, net_io);
    if (J_LIKELY(list))
    {
        net->io_list = hm_list_delete_link(net->io_list, list);
        if (notify && net->on_fin)
        {
        	hm_mutex_unlock(net->lock);
            (*net->on_fin)(net_io, err, init_data);
            hm_mutex_lock(net->lock);
        }
        return 1;
    }

    return 0;
}


static __inline__ int
_hm_net_kill_io(JNet *net, JNetIO *net_io,
    int notify, int err)
{
    int found;

    hm_mutex_lock(net->lock);
    found = __hm_net_kill_io(net, net_io, NULL, notify, err);
    hm_mutex_unlock(net->lock);

    if (found)
    {
        hm_net_io_kill(net_io);
        hm_net_io_unref(net_io);   /* decrease ref owned by #net::io_list */
        return 0;
    }

    return -E_NONETIO;
}


static __inline__ int
__hm_net_add_io(JNet *net, JNetIO *net_io, void *init_data, int notify)
{
	HMList *list;
    int rc = 0;

    if (net->killed)
    {
        return -E_NETDIE;
    }

#ifdef JPF_DEBUG
    BUG_ON(hm_list_find(net->io_list, net_io));
#else
	list = hm_list_find(net->io_list, net_io);
	if (list)
	{
		return -EEXIST;	
	}
#endif

	net->io_list = hm_list_add(net->io_list, net_io);
    hm_net_io_set_owner(net_io, net);
    hm_net_ref(net);
    hm_net_io_ref(net_io);

    if (notify && net->on_init)
    {
    	hm_mutex_unlock(net->lock);

        rc = (*net->on_init)(net_io, init_data);
		if (rc)
		{
			_hm_net_kill_io(net, net_io, 0, 0);
		}

        hm_mutex_lock(net->lock);
    }

    return rc;
}


__export int
hm_net_add_io(JNet *net, JNetIO *net_io, void *init_data, int notify)
{
    int rc;
    J_ASSERT(net != NULL && net_io != NULL);

    hm_mutex_lock(net->lock);
    rc = __hm_net_add_io(net, net_io, init_data, notify);
    hm_mutex_unlock(net->lock);

    if (!rc)
    {
   	 	hm_scheduler_sched_io(net->scheduler, net_io);
   	}

    return rc;
}


__export JNetIO *
hm_net_create_io(JNet *net, JConnection *conn, J2Proto *proto,
	JIOEst on_est, int *err)
{
    JNetIO *io;
    int rc;
    J_ASSERT(net != NULL && conn != NULL);

    io = hm_net_io_new(conn, proto->ll_proto, 
        proto->hl_proto, proto->init_data, err);
    if (J_UNLIKELY(!io))
    {
    	hm_connection_close(conn);
        return NULL;
    }

	hm_net_io_set_ester(io, on_est);
    rc = hm_net_add_io(net, io, proto->init_data, 0);
    if (rc)
    {
        if (err)
            *err = rc;

        hm_net_io_kill(io);
        hm_net_io_unref(io);
        return NULL;
    }

    return io;
}


__export JNetIO *
hm_net_create_listen_io(JNet *net, JConnection *conn, J2Proto *proto,
    int *err)
{
    JNetIO *io;
    int rc;
    J_ASSERT(net != NULL && conn != NULL && proto != NULL);

    io = hm_net_listen_io_new(conn, proto->ll_proto,
        proto->hl_proto, proto->init_data, err);
    if (J_UNLIKELY(!io))
    {
    	hm_connection_close(conn);
        return NULL;
    }

    rc = hm_net_add_io(net, io, proto->init_data, 0);
    if (rc)
    {
        if (err)
            *err = rc;

        hm_net_io_kill(io);
        hm_net_io_unref(io);
        return NULL;
    }

    return io;
}


__export JNetIO *
hm_net_create_listen_io_2(JNet *net, struct sockaddr *sa, J2Proto *proto, int *err)
{
    JConnection *conn;
    int rc;

    conn = hm_connection_new(sa, CF_TYPE_TCP|CF_FLGS_NONBLOCK, err);
    if (conn)
    {
        rc = hm_connection_listen(conn);
        if (J_UNLIKELY(rc < 0))
        {
            hm_connection_close(conn);
            if (err)
                *err = rc;
            return NULL;
        }

        return hm_net_create_listen_io(net, conn, proto, err);
    }

    return NULL;
}


__export int
hm_net_write_io(JNetIO *net_io, void * msg)
{
    return hm_net_io_write_message(net_io, msg);
}


__export JNetIO *
hm_net_ref_io(JNetIO *net_io)
{
    return hm_net_io_ref(net_io);
}


__export void
hm_net_unref_io(JNetIO *net_io)
{
    hm_net_io_unref(net_io);
}


__export void
hm_net_set_io_ttd(JNetIO *net_io, int milli_sec)
{
    hm_net_io_set_ttd(net_io, milli_sec);
}


__export void
hm_net_set_io_reader(JNetIO *net_io, JIOReader reader, void *init_data)
{
	hm_net_io_set_reader(net_io, reader, init_data);
}


static __inline__ void
__hm_net_establish_io(JNet *net, JNetIO *net_io)
{
	HMList *list;

    list = hm_list_find(net->io_list, net_io);
    if (J_LIKELY(list))
    {
    	hm_mutex_unlock(net->lock);
		/* if net_io may be killed in on_establish() */
    	hm_net_io_on_establish(net_io);
    	hm_mutex_lock(net->lock);
    }
}


__export void
hm_net_establish_io(JNet *net, JNetIO *net_io)
{
	J_ASSERT(net != NULL && net_io != NULL);

	hm_mutex_lock(net->lock);
	__hm_net_establish_io(net, net_io);
	hm_mutex_unlock(net->lock);
}


__export void
hm_net_async_kill_io(JNet *net, JNetIO *net_io, void *init_data, int err)
{
    int found;

    hm_mutex_lock(net->lock);
    found = __hm_net_kill_io(net, net_io, init_data, 1, err);
    hm_mutex_unlock(net->lock);

    if (found)
    {   /* decrease ref owned by #net::io_list */
        hm_net_io_unref(net_io);
    }
}


__export int
hm_net_kill_io(JNet *net, JNetIO *net_io)
{
    J_ASSERT(net != NULL && net_io != NULL);

    return _hm_net_kill_io(net, net_io, 0, 0);
}


__export void *
hm_set_timer(int timeout, int (*on_timer)(void*), void *data)
{
	return hm_scheduler_add_timer(timeout, on_timer, data);
}


__export void
hm_del_timer(void *handle)
{
	hm_scheduler_del_timer(handle);
}


__export void
hm_net_set_io_u(JNetIO *net_io, void *u, JIOFinUser *fu)
{
	hm_net_io_set_u(net_io, u, (JNetIOFin)fu);
}


__export void *
hm_net_get_io_u(JNetIO *net_io)
{
	return hm_net_io_get_u(net_io);
}


__export char *
hm_net_get_io_host_name(JNetIO *net_io, char *ip)
{
	if (!net_io)
		return NULL;
	return hm_net_io_get_host(net_io, ip);
}


__export char *
hm_net_get_io_peer_name(JNetIO *net_io, char *ip)
{
	if (!net_io)
		return NULL;
	return hm_net_io_get_peer(net_io, ip);
}

//:~ End
