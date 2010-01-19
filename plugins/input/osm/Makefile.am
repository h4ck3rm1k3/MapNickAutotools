pkglibdir = $(libdir)/mapnik/input

if HAVE_LIBXML2

pkglib_LTLIBRARIES = osm.la

osm_la_SOURCES = \
	basiccurl.cpp\
	basiccurl.h\
	dataset_deliverer.cpp\
	dataset_deliverer.h\
	osm.cpp \
	osm.h\
	osm_datasource.cpp \
	osm_datasource.hpp \
	osm_featureset.cpp \
	osm_featureset.hpp \
	osmparser.cpp\
	osmparser.h\
	osmtagtypes.h\
	render.cpp

osm_la_CXXFLAGS = \
  -Wall \
  ${PROFILING_CFLAGS} \
  ${TRACING_CFLAGS} \
	-I../../../include \
	${LIBXML2_CFLAGS} \
	${PROFILING_CFLAGS} \
	${TRACING_CFLAGS} \
	${PNG_CFLAGS} \
	${FREETYPE2_CFLAGS} \
	${AGG_CFLAGS} \
	${JPEG_CFLAGS} \
	${TIFF_CFLAGS} \
	${PROJ_CFLAGS} \
	${LTDL_CFLAGS} \
	${BOOST_CPPFLAGS} \
	${LIBXML2_CFLAGS} \
	${CAIRO_CFLAGS} \
	-D_REENTRANT -I/usr/include/cairomm-1.0 -I/usr/include/cairo -I/usr/include/sigc++-2.0 -I/usr/lib/sigc++-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/directfb -I/usr/include/libpng12 \
	${FT2_CFLAGS}

osm_la_LIBADD = \
	${LIBXML2_LIBS} ${FT2_LIBS}

osm_la_LDFLAGS = \
	-module \
	-avoid-version \
	-shrext .input

endif



GCH_FILES=  \
	stdinc.hpp.gch				


BUILT_SOURCES = $(GCH_FILES) 


%.hpp.gch: %.hpp
	/usr/local/bin/g++ -DHAVE_CONFIG_H -I. -I../.. -I../../../include -pg -DMAPNIK_DEBUG -I/usr/include/libpng12 -I/usr/include/freetype2 -I/media/NewFoundSpace/2010/01/mapnik/agg/include -I/usr/local/include -I/usr/include/libxml2 -D_REENTRANT -I/usr/include/cairomm-1.0 -I/usr/include/cairo -I/usr/include/sigc++-2.0 -I/usr/lib/sigc++-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/directfb -I/usr/include/libpng12 -Winvalid-pch -dD  -c $< 



## File created by the gnome-build tools

