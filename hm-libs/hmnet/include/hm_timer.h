/*
 * jpf_timer.h
 *
 * This file declares interfaces for timer.
 *
 * Copyright(c) by HiMickey, 2010~2014
 * Author:
*/

#ifndef __J_TIMER_H__
#define __J_TIMER_H__

#include "hmlib.h"

typedef int (*JOnTimer)(void *data);

typedef struct _JTimer JTimer;
struct _JTimer
{
	HMEvent base;
	JOnTimer on_timer;
	void *data;
};

#ifdef __cplusplus
extern "C" {
#endif

JTimer *hm_timer_new(int timeout, JOnTimer on_timer, void *data);
int hm_timer_attach(HMEventLoop *loop, JTimer *timer);
void hm_timer_del(JTimer *timer);

#ifdef __cplusplus
}
#endif


#endif	//__J_TIMER_H__
