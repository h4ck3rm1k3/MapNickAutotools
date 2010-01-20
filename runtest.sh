automake include/mapnik/Makefile;
autoconf
export CC=/usr/local/bin/g++
export CXX=/usr/local/bin/g++
./myconfigure.sh;
# make -C include/mapnik/  cleangch
 make -C include/mapnik/ 
 make -C src/
 make -C plugins/input/osm/
