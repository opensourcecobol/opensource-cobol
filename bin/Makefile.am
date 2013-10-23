## Process this file with automake to produce Makefile.in
##
## Copyright (C) 2004-2009 Roger While
##

bin_PROGRAMS = cobcrun
cobcrun_SOURCES = cobcrun.c

AM_LDFLAGS = $(COB_EXPORT_DYN)
cobcrun_CFLAGS = $(AM_CFLAGS) -I$(top_srcdir)
cobcrun_LDADD = $(top_builddir)/libcob/libcob.la
