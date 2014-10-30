//#include <stdlib.h>
#include <string.h>
#include "hm_queue.h"
#include "hm_mem.h"

#ifdef _DMALLOC
#include "dmalloc.h"
#endif

void hm_queue_init(JQueue *queue)
{
	J_ASSERT(queue != NULL);

	memset(queue, 0, sizeof(*queue));
}


JQueue *hm_queue_new( void )
{
	JQueue *queue = hm_new(JQueue, 1);
	hm_queue_init(queue);
	return queue;
}


void hm_queue_free(JQueue *queue)
{
	J_ASSERT(queue != NULL);

	hm_list_free(queue->head);
	hm_del(queue, JQueue, 1);
}


void hm_queue_clear(JQueue *queue)
{
	J_ASSERT(queue != NULL);

	hm_list_free(queue->head);
	hm_queue_init(queue);
}


unsigned hm_queue_length(JQueue *queue)
{
	J_ASSERT(queue != NULL);

	return queue->count;
}


void hm_queue_push_tail(JQueue *queue, void *data)
{
	J_ASSERT(queue != NULL);

	queue->tail = hm_list_add_tail(queue->tail, data);
	if (queue->tail->next)
		queue->tail = queue->tail->next;
	else
		queue->head = queue->tail;
	++queue->count;
}


void* hm_queue_pop_head(JQueue *queue)
{
	JList *node;
	void *data;
	J_ASSERT(queue != NULL);

	if (queue->head)
	{
		node = queue->head;
		data = hm_list_data(node);

		queue->head = hm_list_next(node);
		if (queue->head)
			queue->head->prev = NULL;
		else
			queue->tail = NULL;

		--queue->count;
		hm_list_free_1(node);
		return data;
	}

	return NULL;
}


void *hm_queue_pop_tail(JQueue *queue)
{
	JList *node;
	void *data;
	
	J_ASSERT(queue != NULL);

	if(!queue->tail)	return NULL;

	node = queue->tail ;
	data = hm_list_data(node);
	
	if(queue->tail == queue->tail )
	{
		queue->head  = queue->tail = NULL; 
	}
	else
	{
		queue->tail = hm_list_prev(node);
	}
	--queue->count;
	hm_list_free_1(node);
	return data;
}

void hm_queue_push_head(JQueue *queue, void *data)
{
	J_ASSERT(queue != NULL);

	if(queue->head)
	{
		queue->head = hm_list_add(queue->head, data);
	}
	else
	{
		queue->head = hm_list_add(queue->head, data);
		queue->tail = queue->head;
	}
	++queue->count;
}
void hm_queue_foreach(JQueue *queue, JVisitCustom func, void *data)
{
	J_ASSERT(queue != NULL);
	
	if(queue->head)
	{
		hm_list_foreach(queue->head, func, data);
	}
}



//:~ End
