noinst_PROGRAMS=test

test_SOURCES=main.c
test_CFLAGS=-fPIC
test_LDADD=
test_LDFLAGS=-D_GNU_SOURCE -L$(top_srcdir)/src/.libs -lhmrtspsvr -fPIC \
	     -lpthread -lm

