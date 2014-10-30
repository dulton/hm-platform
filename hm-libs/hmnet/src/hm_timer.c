#include "hm_timer.h"


static JBool
hm_on_timer_internal(HMEvent *ev, int revents, void *user_data)
{
	JTimer *timer = (JTimer*)ev;

	return (*timer->on_timer)(timer->data) == 0 ? TRUE : FALSE;
}


JTimer *hm_timer_new(int timeout, JOnTimer on_timer, void *data)
{
	JTimer *timer;

	timer = (JTimer*)hm_event_new(sizeof(JTimer), -1, 0);
	timer->on_timer = on_timer;
	timer->data = data;

	hm_event_set_callback((HMEvent*)timer, hm_on_timer_internal, NULL, NULL);
	hm_event_set_timeout((HMEvent*)timer, timeout);

	return timer;
}


int hm_timer_attach(HMEventLoop *loop, JTimer *timer)
{
	J_ASSERT(loop != NULL);

	return !hm_event_loop_attach(loop, (HMEvent*)timer);
}


void hm_timer_del(JTimer *timer)
{
	hm_event_remove((HMEvent*)timer);
}

//:~ End

//for include some necessary file.o
void test()
{
    hm_thread_pool_new(NULL, NULL, 1, NULL);
    base64_free(NULL, 0);
    return ;
}

