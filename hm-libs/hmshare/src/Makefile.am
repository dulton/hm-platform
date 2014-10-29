AUTOMAKE_OPTIONS=foreign
lib_LIBRARIES=libhmshare.a
libhmshare_a_SOURCES=hm_debug.c	\
                      hm_signal.c \
                      hm_conn.c \
                      hm_fragments.c \
                      hm_fragments.h \
                      hm_hlio.c \
                      hm_hlio.h \
                      hm_io.c \
                      hm_io.h \
                      hm_netbuf.c \
                      hm_netbuf.h \
                      hm_net.c \
                      hm_netio.c \
                      hm_watch.c \
                      hm_watch.h \
                      hm_rw_file.c \
                      hm_timer.c

#libhmshare_la_LIBADD=

#libhmshare_la_LDFLAGS=-version-info $(libhmshare_SO_VERSION)
#libhmshare_la_LIBFLAGS=shared

libhmshare_la_CFLAGS=-Wall -g -fno-inline -fstack-protector -fPIC
#libhmshare_la_CXXFLAGS=

libhmshareincludedir=$(prefix)/include/himickey
libhmshareinclude_HEADERS=$(top_srcdir)/include/*.h

