for x in *.hpp; do 
    if [ -s $x.d ]; then
	echo $x.d is done already;
    else
	echo going to do $x.d
	g++ -M -I.. -I/usr/include/agg2/ -I/usr/include/freetype2  -I/usr/include/cairo/  -I /usr/lib/sigc++-2.0/include/ -I /usr/include/sigc++-2.0 -I /usr/include/cairomm-1.0 $x > $x.d
    fi

done
