/* *
 * This file implements event scheduler using glib and libev.
 *
 * Copyright (C) 2012 fangyi <fangyi@szjxj.net>
 * See COPYING for more details
 *
 * */
 
#ifndef __GEV_SCHED_H__
#define __GEV_SCHED_H__

#include "gev.h"

void g_scheduler_init(gint nloop);
void g_scheduler_add(GEvent *source, guint weight);
void g_scheduler_del(GEvent *source);

#endif	/* __GEV_SCHED_H__ */
