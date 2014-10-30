#include "hm_asyncqueue.h"
#include "hm_mem.h"
#include "hm_macros.h"

JAsyncQueue *hm_async_queue_new( void )
{
	JAsyncQueue *queue = hm_new(JAsyncQueue, 1);

	atomic_set(&queue->ref_count, 1);
	hm_queue_init(&queue->queue);
	queue->mutex = hm_mutex_new();
	queue->cond = hm_cond_new();

	return queue;
}


JAsyncQueue *hm_async_queue_ref(JAsyncQueue *queue)
{
	J_ASSERT(queue != NULL);

	atomic_inc(&queue->ref_count);
	return queue;
}


void hm_async_queue_unref(JAsyncQueue *queue)
{//TODO
}


void hm_async_queue_push_unlocked(JAsyncQueue *queue, void *data)
{
	J_ASSERT(queue != NULL && data != NULL);

	hm_queue_push_tail(&queue->queue, data);
	hm_cond_signal(queue->cond);
}


void hm_async_queue_push(JAsyncQueue *queue, void *data)
{
	J_ASSERT(queue != NULL);

	hm_mutex_lock(queue->mutex);
	hm_async_queue_push_unlocked(queue, data);
	hm_mutex_unlock(queue->mutex);
}


void *hm_async_queue_pop_unlocked(JAsyncQueue *queue)
{
	void *data;

	for (;;)
	{
		data = hm_queue_pop_head(&queue->queue);
		if (data)
			return data;

		if (!hm_cond_timed_wait(queue->cond, queue->mutex, NULL))
			break;	/* nerver */
	}

	return NULL;
}


void *hm_async_queue_pop(JAsyncQueue *queue)
{
	void *retval;
	J_ASSERT(queue != NULL);

	hm_mutex_lock(queue->mutex);
	retval = hm_async_queue_pop_unlocked(queue);
	hm_mutex_unlock(queue->mutex);

	return retval;
}


//:~ End
