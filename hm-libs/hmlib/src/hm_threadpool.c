#include "hm_threadpool.h"
#include "hm_thread.h"
#include "hm_mem.h"
#include "hm_asyncqueue.h"


typedef struct _JRealThreadPool JRealThreadPool;

struct _JRealThreadPool
{
	JThreadPool thread_pool;
	JAsyncQueue *queue;
	unsigned max_threads;
	unsigned num_threads;
};


static void *hm_thread_pool_thread_proxy(void *arg)
{
	JRealThreadPool *tp = (JRealThreadPool*)arg;
	void *data;

	while ( TRUE )
	{
		data = hm_async_queue_pop(tp->queue);
		(*tp->thread_pool.func)(data, tp->thread_pool.user_data);
	}

	return NULL;
}

static void hm_thread_pool_start_threads(JRealThreadPool *tp, JError **err)
{
	JError *error = NULL;

	while (tp->max_threads == -1 || tp->num_threads < tp->max_threads)
	{
		hm_thread_create(hm_thread_pool_thread_proxy, tp, 0, &error);
		
		if (error)
		{
			if (err)
				*err = error;
			return;
		}

		++tp->num_threads;

		if (tp->max_threads == -1)
			break;
	}
}


JThreadPool *hm_thread_pool_new(JTPFunc func, void *data, 
	unsigned max_threads, JError **err)
{
	JRealThreadPool *tp;

	tp = hm_new(JRealThreadPool, 1);
	tp->thread_pool.func = func;
	tp->thread_pool.user_data = data;
	tp->queue = hm_async_queue_new();
	tp->max_threads = max_threads ? max_threads : 1;
	tp->num_threads = 0;
	
	hm_thread_pool_start_threads(tp, err);

	return (JThreadPool*)tp;
}


void hm_thread_pool_push(JThreadPool *tp, void *data)
{
	JRealThreadPool *_tp;
	J_ASSERT(tp != NULL && data != NULL);

	_tp = (JRealThreadPool*)tp;
	hm_async_queue_push(_tp->queue, data);
}


void hm_thread_pool_free(JThreadPool *tp, JBool drop, JBool wait)
{
	
}

//:~ End
