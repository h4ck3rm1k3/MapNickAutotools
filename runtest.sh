 automake include/mapnik/Makefile;
export CC=/usr/local/bin/g++
export CXX=/usr/local/bin/g++
./myconfigure.sh;
 make -C include/stdio/bits cleangch
 make -C include/stdio/ cleangch
 make -C include/boost/ cleangch
 make -C include/mapnik/  cleangch

 make -C include/stdio/bits
 make -C include/stdio/ 
 make -C include/boost/ 
 make -C include/mapnik/ 
