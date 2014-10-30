#ifndef __J_SCHEDULER_H__
#define __J_SCHEDULER_H__

#include "hm_netio.h"

typedef struct _JScheduler JScheduler;

#ifdef __cplusplus
extern "C" {
#endif

JScheduler *hm_scheduler_new(int loop_count);
void hm_scheduler_sched_io(JScheduler *sched, JNetIO *io);
void hm_scheduler_release(JScheduler *sched);

void *hm_scheduler_add_timer(int timeout, int (*)(void*), void *data);
void hm_scheduler_del_timer(void *handle);

#ifdef __cplusplus
}
#endif

#endif
