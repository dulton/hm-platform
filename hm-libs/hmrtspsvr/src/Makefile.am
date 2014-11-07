AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=libhmrtspsvr.la
libhmrtspsvr_la_SOURCES=rtsp-server.c \
			rtp/rtp.c \
			rtp/rtp_port.c \
			rtp/rtp_watch.c \
			rtp/rtp_watch.h \
			rtsp/rtsp.c \
			rtsp/rtsp_method_gsparam.c \
			rtsp/rtsp_method_pause.c \
			rtsp/rtsp_method_setup.c \
			rtsp/rtsp_method_teardown.c \
			rtsp/rtsp_method_describe.c \
			rtsp/rtsp_method_options.c \
			rtsp/rtsp_method_play.c \
			rtsp/rtsp_methods.h \
			utils/bufferqueue.c \
			utils/fdset.c \
			utils/ports.c \
 			media/demuxer.c \
			media/demuxer_module.h \
			media/media.c \
			media/mediaparser.c \
			media/mediautils.c \
			media/parser/hma.c \
			media/parser/hmv.c \
			media/demuxer/demuxer_hm.c \
			media/demuxer/demuxer_ls.c \
			reverse_connector/reverse_connector.c \
			log/rc_log.c

#hmrtspsvr_la_LIBADD=

libhmrtspsvr_la_LDFLAGS=-version-info $(LIBHMRTSPSVR_SO_VERSION) -L$(HMDEV_LIB_INSTALL)/lib -lev
libhmrtspsvr_la_LIBFLAGS=shared

libhmrtspsvr_la_CFLAGS=-Wall -g -fno-inline -fstack-protector -fPIC
#hmrtspsvr_la_CXXFLAGS=

libhmrtspsvrincludedir=$(prefix)/include/himickey
libhmrtspsvrinclude_HEADERS=$(top_srcdir)/include/*.h

