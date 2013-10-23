## Process this file with automake to produce Makefile.in
##
## Copyright (C) 2003-2009 Keisuke Nishida
## Copyright (C) 2008-2009 Roger While
##

SUBDIRS = cobol85

TESTS = $(srcdir)/syntax \
	$(srcdir)/run \
	$(srcdir)/run-O \
	$(srcdir)/data-rep \
	$(srcdir)/data-rep-O

syntax_DEPENDENCIES = \
	syntax.at \
	syntax.src/copy.at \
	syntax.src/definition.at \
	syntax.src/expression.at \
	syntax.src/multiply.at \
	syntax.src/redefines.at \
	syntax.src/value.at \
	syntax.src/move.at \
	syntax.src/set.at \
	syntax.src/occurs.at \
	syntax.src/subscripts.at

run_DEPENDENCIES = \
	run.at \
	run.src/fundamental.at \
	run.src/accept.at \
	run.src/initialize.at \
	run.src/misc.at \
	run.src/ref-mod.at \
	run.src/subscripts.at \
	run.src/extensions.at \
	run.src/return-code.at \
	run.src/functions.at

data_rep_DEPENDENCIES = \
	data-rep.at \
	data-rep.src/binary.at \
	data-rep.src/display.at \
	data-rep.src/packed.at \
	data-rep.src/pointer.at \
	data-rep.src/numeric-dump.cob \
	data-rep.src/numeric-display.cob

EXTRA_DIST = $(srcdir)/package.m4 $(TESTS) \
	$(syntax_DEPENDENCIES) \
	$(run_DEPENDENCIES) \
	$(data_rep_DEPENDENCIES)

DISTCLEANFILES = atconfig

all: $(TESTS)

clean-local:
	rm -rf *.dir *.log

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	@echo "creating $(srcdir)/package.m4"
	@{								   \
	  echo '# Signature of the current package.';			   \
	  echo 'm4_define([AT_PACKAGE_NAME],	  [@PACKAGE_NAME@])';	   \
	  echo 'm4_define([AT_PACKAGE_TARNAME],	  [@PACKAGE_TARNAME@])';   \
	  echo 'm4_define([AT_PACKAGE_VERSION],	  [@PACKAGE_VERSION@])';   \
	  echo 'm4_define([AT_PACKAGE_STRING],	  [@PACKAGE_STRING@])';    \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [@PACKAGE_BUGREPORT@])'; \
	} > $(srcdir)/package.m4

$(srcdir)/%: $(srcdir)/%.at $(srcdir)/package.m4
	autom4te --language=autotest -I $(srcdir) -I $@.src -o $@ $<
	chmod +x $@

$(srcdir)/syntax: $(syntax_DEPENDENCIES)
$(srcdir)/run: $(run_DEPENDENCIES)
$(srcdir)/data-rep: $(data_rep_DEPENDENCIES)
