AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=libhmlib.la
libhmlib_la_SOURCES=hm_mem.c \
 		   hm_list.c \
		   hm_queue.c \
		   hm_asyncqueue.c \
		   hm_thread.c \
		   hm_thread_posix.c \
		   hm_thread_windows.c \
		   hm_threadpool.c \
		   hm_event.c \
		   hm_sched.c \
		   hm_base64.c
libhmlib_la_LIBADD=$(HOME)/usr/lib/libev.a
libhmlib_la_LDFLAGS=-no-undefined -version-info $(LIBHMLIB_SO_VERSION)

libhmlibincludedir=$(prefix)/include/himickey
libhmlibinclude_HEADERS=$(top_srcdir)/include/*.h
