#ifndef __J_ASYNCQUEUE_H__
#define __J_ASYNCQUEUE_H__

#include "hm_queue.h"
#include "hm_thread.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _JAsyncQueue JAsyncQueue;

struct _JAsyncQueue
{
	atomic_t ref_count;
	JQueue queue;
	JMutex *mutex;
	JCond *cond;
};

JAsyncQueue *hm_async_queue_new( void );
JAsyncQueue *hm_async_queue_ref(JAsyncQueue *queue);
void hm_async_queue_unref(JAsyncQueue *queue);
void hm_async_queue_push(JAsyncQueue *queue, void *data);
void *hm_async_queue_pop(JAsyncQueue *queue);

#ifdef __cplusplus
}
#endif


#endif	/* __J_ASYNCQUEUE_H__ */
