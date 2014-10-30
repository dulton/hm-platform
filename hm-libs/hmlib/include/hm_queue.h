#ifndef __J_QUEUE_H__
#define __J_QUEUE_H__

#include "hm_list.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _JQueue JQueue;
struct _JQueue
{
	JList	*head;
	JList	*tail;
	unsigned count;		
};

JQueue *hm_queue_new( void );
void hm_queue_init(JQueue *queue);
void hm_queue_free(JQueue *queue);
void hm_queue_clear(JQueue *queue);
unsigned hm_queue_length(JQueue *queue);
void hm_queue_push_tail(JQueue *queue, void *data);
void* hm_queue_pop_head(JQueue *queue);

void *hm_queue_pop_tail(JQueue *queue);
void hm_queue_push_head(JQueue *queue, void *data);
void hm_queue_foreach(JQueue *queue, JVisitCustom func, void *data);


#ifdef __cplusplus
}
#endif

#endif	/* __J_QUEUE_H__ */
