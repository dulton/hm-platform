#ifndef __J_THREAD_H__
#define __J_THREAD_H__

#include "hm_error.h"
#include "hm_types.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*JThreadFunc)(void *data);
typedef void (*JDestroyNotify)(void *data);

typedef struct _JThread JThread;
typedef struct _JMutex JMutex;
typedef struct _JCond JCond;
typedef struct _JPrivate JPrivate;

typedef enum
{
	THREAD_PRIORITY_LOW,
	THREAD_PRIORITY_NORMAL,
	THREAD_PRIORITY_HIGH,
	THREAD_PRIORITY_URGENT
}JThreadPriority;

struct _JThread
{
	JThreadFunc func;
	void *data;
	int joinable;
	JThreadPriority priority;
};

typedef struct _JThreadInterfaces JThreadInterfaces;

struct _JThreadInterfaces
{
	JMutex* (*mutex_new)(void);
	void (*mutex_lock)(JMutex *mutex);
	int  (*mutex_trylock)(JMutex *mutex);
	void (*mutex_unlock)(JMutex *mutex);
	void (*mutex_free)(JMutex *mutex);

	JCond* (*cond_new)(void);
	void (*cond_signal)(JCond *cond);
	void (*cond_broadcast)(JCond *cond);
	void (*cond_wait)(JCond *cond, JMutex *mutex);
	int  (*cond_timed_wait)(JCond *cond, JMutex *mutex, JTimeVal *end_time);
	void (*cond_free)(JCond *cond);

	void (*thread_create)(JThreadFunc func, void *arg, unsigned long stack_size,
						int joinable, int bound, JThreadPriority priority,
                        void *thread, JError **error);

	void (*thread_yield)(void);
	void (*thread_join)(void *thread);
	void (*thread_exit)(void);
	void (*thread_set_priority)(void *thread, JThreadPriority priority);
	void (*thread_self)(void *thread);
	int  (*thread_equal)(void *thread1, void *thread2);

	JPrivate* (*private_new)(JDestroyNotify destructor);
	void* (*private_get)(JPrivate *private_key);
	void (*private_set)(JPrivate *private_key, void *data);
};

extern JThreadInterfaces *jlib_thread_ops;

#define J_THREAD_INVOKE(op, arglist) \
	(*jlib_thread_ops->op) arglist

#define hm_mutex_new() J_THREAD_INVOKE(mutex_new, ())
#define hm_mutex_lock(mutex) J_THREAD_INVOKE(mutex_lock, (mutex))
#define hm_mutex_trylock(mutex) J_THREAD_INVOKE(mutex_trylock, (mutex))
#define hm_mutex_unlock(mutex) J_THREAD_INVOKE(mutex_unlock, (mutex))
#define hm_mutex_free(mutex) J_THREAD_INVOKE(mutex_free, (mutex))
#define hm_cond_new() J_THREAD_INVOKE(cond_new, ())
#define hm_cond_signal(cond) J_THREAD_INVOKE(cond_signal, (cond))
#define hm_cond_broadcast(cond) J_THREAD_INVOKE(cond_broadcast, (cond))
#define hm_cond_wait(cond, mutex) J_THREAD_INVOKE(cond_wait, ((cond), (mutex)))
#define hm_cond_timed_wait(cond, mutex, abs_time) \
	J_THREAD_INVOKE(cond_timed_wait, ((cond), (mutex), (abs_time)))
#define hm_cond_free(cond) J_THREAD_INVOKE(cond_free, (cond))
#define hm_thread_yield() J_THREAD_INVOKE(thread_yield, ())
#define hm_private_new(destructor) J_THREAD_INVOKE(private_new, (destructor))
#define hm_private_get(key) J_THREAD_INVOKE(private_get, (key))
#define hm_private_set(key, data) J_THREAD_INVOKE(private_set, ((key), (data)))

JThread *hm_thread_create_internal(JThreadFunc func, void *arg, 
	unsigned long stack_size,int joinable, int bound, JThreadPriority priority,
	JError **error);

#define hm_thread_create(func, arg, joinable, error) \
	hm_thread_create_internal(func, arg, 0, joinable, 0, THREAD_PRIORITY_NORMAL, error)

void *hm_thread_join(JThread *thread);
void hm_thread_exit(void *retval);
void hm_thread_set_priority(JThread *thread, JThreadPriority priority);
JThread *hm_thread_self( void );
JBool hm_thread_equal(JThread *thread1, JThread *thread2);


#ifdef __cplusplus
}
#endif

#endif	/* __J_THREAD_H__ */
