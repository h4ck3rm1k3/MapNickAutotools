## Process this file with automake to produce Makefile.in
## Created by Anjuta

ACLOCAL_AMFLAGS=-I m4

SUBDIRS = agg \
	src \
	plugins\
	include \
	bindings \
	utils \
	demo 


mapnikdocdir = ${prefix}/doc/mapnik
mapnikdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	INSTALL

EXTRA_DIST = $(mapnikdoc_DATA) \
	$(fonts_DATA)\
	$(includes_HEADERS)

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

