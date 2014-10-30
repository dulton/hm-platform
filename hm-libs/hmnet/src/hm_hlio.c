/*
 * hm_hlio.c
 *
 * This file implements high level io, payload layer.
 *
 * Copyright(c) by HiMickey, 2010~2014
 * Author:
*/

#include "hm_hlio.h"
#include "hm_debug.h"
#include "hm_errno.h"


static JWatch *
hm_hl_io_create(JIO *io, JConnection *conn)
{
	JHlIO *listen_io;

	listen_io = (JHlIO*)io;
	return (JWatch*)hm_hl_io_new(
		conn,
		io->proto,
		listen_io->proto
	);
}


static void
hm_hl_listen_io_on_error(JIO *io, int rw, int why)
{
	hm_error(
		"Net Listen IO '%p' error, Err: '%d'.\n", io, why
	);

	FATAL_ERROR_EXIT;
}


static JIOFuncs jxhm_high_level_listen_io_funcs =
{
	.create		= hm_hl_io_create,
	.error		= hm_hl_listen_io_on_error
};


static int
hm_hl_io_recv(JIO *io, char *start, size_t size,
	void *from_lower)
{
	int rc;
	JPayloadProto *proto;
	JHlIO *hl_io;
	void *msg;

	hl_io = (JHlIO*)io;
	proto = hl_io->proto;
	BUG_ON(!proto);

	if (!proto->get_payload)
		return -E_PRONOTIMPL;

	if ((msg = (*proto->get_payload)(start, size, from_lower)))
	{
		rc = hm_watch_recv_message((JWatch*)hl_io, msg);
		if (rc)
		{
			BUG_ON(!proto->destroy_pointer);
			(*proto->destroy_pointer)(msg, rc);
		}
	}

	return 0;
}


static int
hm_hl_io_format(JIO *io, void *msg, char buf[],
	size_t size)
{
	JPayloadProto *proto;
	JHlIO *hl_io;

	hl_io = (JHlIO*)io;
	proto = hl_io->proto;

	BUG_ON(!proto);

	if (proto->put_payload)
	{
		return (*proto->put_payload)(msg, buf, size);
	}

	return 0;
}


static void
hm_hl_io_on_error(JIO *io, int rw, int why)
{
	hm_warning(
		"Net IO '%p' %s error, Err: '%d', report from hl layer.\n",
		io, rw ? "write" : "read", why
	);
}


static void
hm_hl_io_on_close(JIO *io, int async)
{
	hm_print(
		"Net IO '%p' closed%s, report from hl layer.\n",
		io, async ? " by peer" : ""
	);
}


static JIOFuncs jxhm_high_level_io_funcs =
{
	.recv		= hm_hl_io_recv,
	.format		= hm_hl_io_format,
	.error		= hm_hl_io_on_error,
	.close		= hm_hl_io_on_close
};


JHlIO *
hm_hl_io_new(JConnection *conn, JPacketProto *ll_proto,
	JPayloadProto *hl_proto)
{
	JHlIO *hl_io;
	J_ASSERT(conn != NULL && ll_proto != NULL && hl_proto != NULL);

	hl_io = (JHlIO*)hm_io_new(
		conn,
		ll_proto,
		&jxhm_high_level_io_funcs,
		sizeof(JHlIO)
	);

	if (hl_io)
	{
		hl_io->proto = hl_proto;
	}

	return hl_io;
}


JHlIO *
hm_hl_listen_io_new(JConnection *conn, JPacketProto *ll_proto,
	JPayloadProto *hl_proto)
{
	JHlIO *hl_io;
	J_ASSERT(conn != NULL && ll_proto != NULL && hl_proto != NULL);

	hl_io = (JHlIO*)hm_listen_io_new(
		conn,
		ll_proto,
		&jxhm_high_level_listen_io_funcs,
		sizeof(JHlIO)
	);

	if (hl_io)
	{
		hl_io->proto = hl_proto;
	}

	return hl_io;
}


//:~ End
