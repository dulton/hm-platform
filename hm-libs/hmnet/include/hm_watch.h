/*
 * hm_watch.h
 *
 * This file declares watch structure and interfaces.
 *
 * Copyright(c) by HiMickey, 2010~2014
 * Author:
*/

#ifndef __J_WATCH_H__
#define __J_WATCH_H__

#include "hmlib.h"
#include "hm_conn.h"
#include "hm_netbuf.h"


#define hm_error(...) fprintf(stderr, __VA_ARGS__);
#define hm_print hm_error
#define hm_debug hm_error
#define hm_warning hm_error


typedef struct _JWatch JWatch;
typedef struct _JWatchFuncs JWatchFuncs;

struct _JWatchFuncs
{
    JWatch *(*create)(JWatch *w, JConnection *conn);

    int (*recv)(JWatch *w, char *buf, size_t size);
    void (*error)(JWatch *w, int rw, int err);
    void (*close)(JWatch *w, int async);

    int (*format)(JWatch *w, void *msg, char buf[], size_t size);
};


struct _JWatch
{
    HMEvent             source;

    JMutex             *lock;

    JNetBuf            *buffer;
    JConnection        *conn;
    JWatchFuncs        *funcs;

    JTimeVal           next_timeout;       /* timeout point */

    int                w_pending;
    int                killed;

    void               *priv_data;
};

#ifdef __cplusplus
extern "C" {
#endif

JWatch *hm_watch_create(JConnection *conn,
    JWatchFuncs *funcs, int size);

JWatch *hm_listen_watch_create(JConnection *conn,
    JWatchFuncs *funcs, int size);

void hm_watch_attach(JWatch *watch, HMEventLoop *loop);

int hm_watch_recv_message(JWatch *watch, void *msg);
int hm_watch_write_message(JWatch *watch, void *msg);

void hm_watch_kill(JWatch *watch);

void hm_watch_ref(JWatch *watch);
void hm_watch_unref(JWatch *watch);

void hm_watch_set_private(JWatch *watch, void *priv_data);
JBool hm_watch_set_conn_ttd(JWatch *watch, int milli_sec);

char *hm_watch_get_host(JWatch *watch, char *ip);
char *hm_watch_get_peer(JWatch *watch, char *ip);

#ifdef __cplusplus
}
#endif

#endif  //__J_WATCH_H__
