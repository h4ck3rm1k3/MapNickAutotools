pkglibdir = $(libdir)/mapnik/input

if HAVE_LIBXML2
bin_PROGRAMS = render 

render_SOURCES= render.cpp
render_CXXFLAGS =   -Wall   $(DEFINES) $(INCLUDE)  ${PROFILING_CFLAGS} ${GCH_CFLAGS}  ${TRACING_CFLAGS} -I../../../include \
	${LIBXML2_CFLAGS} \
	`pkg-config --cflags cairomm-1.0` \
	${FT2_CFLAGS} \
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

# 	-lsicudata -lsicui18n -lsicuio -lsicule -lsiculx -lsicuuc 

render_LDFLAGS = \
	/usr/lib/libicu*.so.40 \
	-lproj -ljpeg  -lpython2.5 \
	-licudata  -licuio  -liculx  -licuuc -licui18n  -licule  -licutu \
	-lboost_date_time -lboost_filesystem -lboost_graph -lboost_iostreams -lboost_math_c99f -lboost_math_c99l -lboost_math_c99 -lboost_math_tr1f -lboost_math_tr1l -lboost_math_tr1 -lboost_prg_exec_monitor -lboost_program_options -lboost_python -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_unit_test_framework -lboost_wave -lboost_wserialization \
	${LIBXML2_LIBS} ${FT2_LIBS} -lboost_system \
	`pkg-config --libs  cairomm-1.0` \
	../../../../src/libmapnik.la

endif



## File created by the gnome-build tools

