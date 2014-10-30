#!/bin/sh
SUBDIRS=src test
CURRENTPATH=$(shell /bin/pwd)
INCLUDES=-I$(CURRENTPATH) \
	 -I$(CURRENTPATH)/include \
	 -I$(HOME)/usr/include \
	 -I$(HOME)/usr/include/himickey

export INCLUDES

ACLOCAL_AMFLAGS=-I m4

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA=libhmmb.pc

