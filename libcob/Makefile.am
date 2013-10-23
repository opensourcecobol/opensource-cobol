## Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003-2009 Keisuke Nishida
## Copyright (C) 2008-2009 Roger While
##

lib_LTLIBRARIES = libcob.la
libcob_la_SOURCES = common.c call.c strings.c move.c numeric.c \
	intrinsic.c fileio.c termio.c screenio.c

libcob_la_CFLAGS = $(AM_CFLAGS) $(LIBCOB_CFLAGS) -I$(top_srcdir)
libcob_la_LIBADD = $(LIBCOB_LIBS)
libcob_la_LDFLAGS = -version-info 1:0:0 -no-undefined
AM_LDFLAGS = $(COB_FIX_LIB)

EXTRA_DIST = coblocal.h
pkgincludedir = $(includedir)/libcob
pkginclude_HEADERS = byteswap.h common.h move.h numeric.h exception.def \
	termio.h fileio.h screenio.h strings.h call.h intrinsic.h \
	codegen.h system.def
