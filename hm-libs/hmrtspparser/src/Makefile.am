AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=libhmrtspparser.la
libhmrtspparser_la_SOURCES=base64.c \
			   rtspctx.c \
			   rtspdefs.c \
			   rtspmsg.c \
			   rtspparse.c \
			   rtsptransport.c \
                           rtspurl.c \
                           sdp.c

hmrtspparser_la_LIBADD=

libhmrtspparser_la_LDFLAGS=-no-undefined -version-info $(LIBHMRTSPPARSER_SO_VERSION)
libhmrtspparser_la_LIBFLAGS=shared

libhmrtspparser_la_CFLAGS=-Wall -fno-inline -fstack-protector -fPIC
libhmrtspparser_la_CXXFLAGS=

libhmrtspparserincludedir=$(prefix)/include/himickey
libhmrtspparserinclude_HEADERS=$(top_srcdir)/include/*.h

