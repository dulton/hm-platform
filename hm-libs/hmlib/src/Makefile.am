AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=libhmlib.la
libhmlib_la_SOURCES=j_mem.c \
 		   j_list.c \
		   j_queue.c \
		   j_asyncqueue.c \
		   j_thread.c \
		   j_thread_posix.c \
		   j_thread_windows.c \
		   j_threadpool.c \
		   j_event.c \
		   j_sched.c \
		   j_base64.c
libhmlib_la_LIBADD=$(HOME)/usr/lib/libev.a
libhmlib_la_LDFLAGS=-no-undefined -version-info $(LIBHMLIB_SO_VERSION)

libhmlibincludedir=$(prefix)/include/himickey
libhmlibinclude_HEADERS=$(top_srcdir)/include/*.h \
		      $(HOME)/usr/include/*.h 


