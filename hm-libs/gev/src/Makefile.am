AUTOMAKE_OPTIONS=foreign
lib_LIBRARIES=libhmgev.a
libhmgev_a_SOURCES=gev.c \
                   gevsched.c

libhmgev_la_LIBADD=-L$(HOME)/usr/lib -lev

#libhmgev_la_LDFLAGS=-version-info $(libhmgev_SO_VERSION)
#libhmgev_la_LIBFLAGS=shared

libhmgev_la_CFLAGS=-Wall -g -fno-inline -fstack-protector -fPIC
#libhmgev_la_CXXFLAGS=

libhmgevincludedir=$(prefix)/include/himickey
libhmgevinclude_HEADERS=$(top_srcdir)/include/*.h

