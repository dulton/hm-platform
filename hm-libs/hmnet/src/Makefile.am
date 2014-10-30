AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=libhmnet.la
libhmnet_la_SOURCES=hm_conn.c hm_hlio.c hm_io.c hm_netbuf.c hm_net.c hm_netio.c hm_scheduler.c hm_timer.c hm_watch.c
libhmnet_la_LIBADD=$(HOME)/usr/lib/libhmlib.a
libhmnet_la_LDFLAGS=-no-undefined -version-info $(LIBHMNET_SO_VERSION)
libhmnet_la_CFLAGS=-fPIC
libhmnet_la_CXXFLAGS=

libhmnetincludedir=$(prefix)/include/himickey
libhmnetinclude_HEADERS=$(top_srcdir)/include/*.h 



