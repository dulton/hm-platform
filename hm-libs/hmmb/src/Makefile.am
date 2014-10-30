AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=libhmmb.la
libhmmb_la_SOURCES=mb_api.c mb_basic.c mb_cu.c mb_pu.c
libhmmb_la_LDFLAGS=-no-undefined -version-info $(LIBHMMB_SO_VERSION) -lpthread -lrt
libhmmb_la_CFLAGS=-fPIC
libhmmb_la_CXXFLAGS=-fPIC

libhmmbincludedir=$(prefix)/include/himickey
libhmmbinclude_HEADERS=$(top_srcdir)/include/mb_api.h 

