AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=libhmxml.la
libhmxml_la_SOURCES=hm_xmlmem.c xml-tree.c xml-merge.c xml-parse.c hm_transform.c hm_xmlhandler.c hm_xmlmsg.c 
libhmxml_la_LIBADD=$(HOME)/usr/lib/libmxml.a
libhmxml_la_LDFLAGS=-no-undefined -version-info $(LIBHMXML_SO_VERSION)
libhmxml_la_CFLAGS=
libhmxml_la_CXXFLAGS=


libhmxmlincludedir=$(prefix)/include/himickey
libhmxmlinclude_HEADERS=$(top_srcdir)/include/hm_sdk.h \
		       $(top_srcdir)/include/hm_packet.h \
		       $(top_srcdir)/include/hm_xmlmsg.h \
		       $(top_srcdir)/include/hm_transform.h \
 		       $(top_srcdir)/include/proxy_info.h 

