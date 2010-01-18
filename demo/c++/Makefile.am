bin_PROGRAMS = cppdemo 

cppdemo_SOURCES= rundemo.cpp missing.cpp

CXX = g++

cppdemo_CXXFLAGS = \
  -Wall \
  $(DEFINES) $(INCLUDE) -Wall \
  ${PROFILING_CFLAGS} ${GCH_CFLAGS}\
  ${TRACING_CFLAGS} \
	-I../../include \
	${LIBXML2_CFLAGS} \
	`pkg-config --cflags cairomm-1.0` \
	${FT2_CFLAGS}

cppdemo_LDFLAGS = \
	${LIBXML2_LIBS} ${FT2_LIBS} -lboost_system \
	`pkg-config --libs  cairomm-1.0` \
	../../src/libmapnik.la 


