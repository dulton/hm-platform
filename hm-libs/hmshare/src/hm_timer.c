/*
 * hm_timer.c
 *
 * This file implements timer
 *
 * Copyright(c) by HiMickey, 2010~2014
 * Author:
*/

#include "hm_timer.h"
#include "hm_debug.h"

struct _HmTimerEngine
{
	GMainContext	*context;
	GMainLoop		*loop;
	GThread			*th_loop;
};

static gpointer hm_timer_thread_loop(gpointer user_data);
static HmTimerEngine *global_timer_engine = NULL;
static volatile gsize g_init_global_timer_engine_volatile = 0;

HmTimerEngine *
hm_timer_engine_new( void )
{
	HmTimerEngine *eng;

	eng = g_new0(HmTimerEngine, 1);
	if (!eng)	/* glib, unlikely */
		return NULL;

	eng->context = g_main_context_new();
	if (!eng->context)
	{
		goto alloc_contex_err;
	}

	eng->loop = g_main_loop_new(eng->context, FALSE);
	if (!eng->loop)
	{
		goto alloc_main_loop_err;
	}	

	eng->th_loop = g_thread_create(
		hm_timer_thread_loop,
		eng,
		TRUE,
		NULL
	);
	if (!eng->th_loop)
	{
		goto alloc_th_loop_err;
	}

	return eng;

alloc_th_loop_err:
	g_main_loop_unref(eng->loop);

alloc_main_loop_err:
	g_main_context_unref(eng->context);

alloc_contex_err:
	g_free(eng);

	return NULL;
}


void
hm_timer_engine_release(HmTimerEngine *eng)
{//:TODO
	G_ASSERT(eng != NULL);

	while (!g_main_loop_is_running(eng->loop))
	{//@{Ugly, but safe.}
		sleep(1);
	}

	g_main_loop_quit(eng->loop);
	g_thread_join(eng->th_loop);
	g_main_loop_unref(eng->loop);
	g_main_context_unref(eng->context);

	g_free(eng);
}


static __inline__ guint
hm_timeout_add_full (gint priority, guint interval,
	GSourceFunc function, gpointer data, GMainContext *context)
{
	GSource *source;
	guint id;

	source = g_timeout_source_new (interval);

	if (priority != G_PRIORITY_DEFAULT)
		g_source_set_priority (source, priority);

	g_source_set_callback (source, function, data, NULL);
	id = g_source_attach (source, context);
	g_source_unref (source);

	return id;
}


guint
hm_timer_engine_set_timer(HmTimerEngine *eng, guint interval,
	HmTimerFun fun, gpointer data)
{
	G_ASSERT(eng != NULL && fun != NULL);

	return hm_timeout_add_full(G_PRIORITY_DEFAULT, interval,
		(GSourceFunc)fun, data, eng->context);
}


void
hm_timer_engine_del_timer(HmTimerEngine *eng, gint id)
{
	GSource *source;
	G_ASSERT(eng != NULL);

	source = g_main_context_find_source_by_id(eng->context, id);
	if (source)
		g_source_destroy(source);
}


static gpointer
hm_timer_thread_loop(gpointer user_data)
{
	HmTimerEngine *eng = (HmTimerEngine*)user_data;

	g_main_loop_run(eng->loop);

	return NULL;
}


static __inline__ void
hm_init_timer( void )
{
	G_ASSERT(!global_timer_engine);

	global_timer_engine = hm_timer_engine_new();
	BUG_ON(!global_timer_engine);
}


guint
hm_set_timer(guint interval, HmTimerFun fun, gpointer data)
{
	guint timer;

	if (g_once_init_enter(&g_init_global_timer_engine_volatile))
	{
		hm_init_timer();
		g_once_init_leave(&g_init_global_timer_engine_volatile, 1);
	}

	timer = hm_timer_engine_set_timer(
		global_timer_engine, interval, fun, data
	);

	if (!timer)
	{
		hm_error(
			"Create timer failed because unknown reason."
		);
		FATAL_ERROR_EXIT;
	}

	return timer;	
}


void
hm_del_timer(guint id)
{
	G_ASSERT(global_timer_engine);
	
	hm_timer_engine_del_timer(global_timer_engine, id);
}


//:~ End
