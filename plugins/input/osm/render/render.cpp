#include <mapnik/stdinc.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/load_map.hpp>
#include <mapnik/agg_renderer.hpp>
/*
#include <mapnik/map.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/box2d.hpp>

#include <mapnik/image_util.hpp>


#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/projection.hpp>
#include <iostream>
#include <cmath>

*/
using namespace mapnik;

using namespace std;


int main(int argc,char *argv[])
{
	if(argc < 6)
	{
		std::cerr<<"Usage: render XMLfile w s e n [OSMfile]" << std::endl;
		exit(0);
	}

	datasource_cache::instance()->register_datasources
		("/usr/local/lib/mapnik/input");
	freetype_engine::register_font
		("/usr/local/lib/mapnik/fonts/DejaVuSans.ttf");

	Map m (800,800);
	load_map(m,argv[1]);
	
	if(argc>6)
	{
	  datasource::parameters p;
		p["type"] = "osm";
		p["file"] = argv[6];
		for(int count=0; count<m.layerCount(); count++)
		{
		  datasource::parameters q = m.getLayer(count).datasource()->params();
		  mapnik::PlugIn* plg= datasource_cache::instance()->create(p);
		  mapnik::PlugIn::datasource_ptr ptr(plg-> create(p));

		  //		  void mapnik::layer::set_datasource()
			m.getLayer(count).set_datasource(ptr);
		}
	}

	box2d<double> bbox (atof(argv[2]),atof(argv[3]),
							atof(argv[4]),atof(argv[5]));
										
	m.zoomToBox(bbox);

	image_32 buf (m.getWidth(), m.getHeight());
	agg_renderer<image_32> r(m,buf);
	r.apply();

	save_to_file<image_data_32>(buf.data(),"blah.png","png");

	return 0;
}
