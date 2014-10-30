#
#        Author:
#        September 6th, 2011
#

vpath %.h $(PROJ_ROOT)/inc

#CC := $(CC) #gcc
# CP := cp
# CFLAGS := -Wall -pg -lc_p -fno-inline -fstack-protector

#INCS += -I$(PROJ_ROOT)/inc -I$(PROJ_ROOT)/lib/inc -I$(PROJ_SHARE)/inc
#LIBS += -rdynamic -ldl -lev

INCS += -I$(_PWD)
INCS += -I$(HOME)/usr/include
LIBS += -L$(HOME)/usr/lib -lev

GLIB_VERSION := 2.0
GLIB_LIBS := glib-${GLIB_VERSION} gobject-${GLIB_VERSION} gthread-${GLIB_VERSION}
INCS += $(shell pkg-config --cflags ${GLIB_LIBS})

LIBS += $(shell pkg-config --libs ${GLIB_LIBS})

OUTPUT_DIR := $(PROJ_ROOT)/bin

.c.o:
	${CC} ${CFLAGS} -o $@ -c $< ${INCS}
