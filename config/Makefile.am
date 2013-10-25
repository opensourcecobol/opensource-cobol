## Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003-2009 Keisuke Nishida
## Copyright (C) 2008-2009 Roger While
##

configdir = @COB_CONFIG_DIR@
config_DATA = default.conf cobol85.conf cobol2002.conf \
	mf.conf ibm.conf mvs.conf bs2000.conf

EXTRA_DIST = $(config_DATA) \
	default-en.conf \
	default-jp.conf \
	jp-compat.conf \
	boundary-limit.conf

install-data-hook:
	$(configDATA_INSTALL) 'default-jp.conf' '$(DESTDIR)$(configdir)/default.conf'
