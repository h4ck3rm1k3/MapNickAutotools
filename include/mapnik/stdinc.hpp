#ifndef INC_STDINC_HPP
#define INC_STDINC_HPP


//#pragma once 

#include "freetype.hpp"
//#include "boostinc.hpp"
//#include "stdioinc.hpp"


#include <mapnik/config.hpp>
#include <mapnik/coord.hpp>
#include <mapnik/box2d.hpp>
//
#include <mapnik/config_error.hpp>
#include <mapnik/color.hpp>
#include <mapnik/css_color_grammar.hpp>
#include <mapnik/color_factory.hpp>


// ctrans prerq
//#include <mapnik/box2d.hpp>
#include <mapnik/coord_array.hpp>
#include <mapnik/projection.hpp>
#include <mapnik/proj_transform.hpp> 

#include <mapnik/ctrans.hpp>
#include <mapnik/global.hpp>
#include <mapnik/image_data.hpp>
#include <mapnik/raster.hpp>

// // mapnik
 #include <mapnik/value.hpp>


// // mapnik
 #include <mapnik/vertex_vector.hpp>
 #include <mapnik/ctrans.hpp>
 #include <mapnik/geom_util.hpp>
#include <mapnik/vertex.hpp>
 #include <mapnik/geometry.hpp>
 #include <mapnik/raster.hpp>

#include <mapnik/feature.hpp>


#include <mapnik/feature_layer_desc.hpp>

#include <mapnik/params.hpp>
#include <mapnik/query.hpp>
#include <mapnik/datasource.hpp>
#include <mapnik/unicode.hpp>
#include <mapnik/memory_datasource.hpp> // neeeds transcode
#include <mapnik/enumeration.hpp>

// // mapnik
 #include <mapnik/value.hpp>
#include <mapnik/expression_node.hpp>


#include <mapnik/expression_grammar.hpp>
#include <mapnik/expression_node.hpp>



 #include <mapnik/utils.hpp>
 #include <mapnik/ctrans.hpp>
 #include <mapnik/geometry.hpp>
 #include <mapnik/text_path.hpp>
 #include <mapnik/font_set.hpp>


#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/font_set.hpp>
#include <mapnik/gamma.hpp>
#include <mapnik/geometry.hpp>
#include <mapnik/geom_util.hpp>

// // mapnik

#include <mapnik/gamma.hpp>
#include <mapnik/image_data.hpp>
#include <mapnik/box2d.hpp>
#include <mapnik/image_view.hpp>
#include <mapnik/global.hpp>


#include <mapnik/graphics.hpp>

#include <mapnik/image_view.hpp>
#include <mapnik/layer.hpp>


#include <mapnik/octree.hpp>

#include <mapnik/plugin.hpp>


#include <mapnik/quad_tree.hpp>


#include <mapnik/stroke.hpp>


#include <mapnik/text_path.hpp>


#include <mapnik/utils.hpp>
#include <mapnik/value.hpp>

#include <mapnik/vertex_vector.hpp>

// mapnik
#include <mapnik/config.hpp>
#include <mapnik/path_expression_grammar.hpp>

#include "feature_style_processor_base.hpp"

#include <mapnik/symbolizer_base.hpp>
#include <mapnik/symbolizer.hpp>





// // mapnik

// #include <mapnik/rule.hpp>
// #include <mapnik/path_expression_grammar.hpp>

#include <mapnik/text_symbolizer.hpp>
#include <mapnik/raster_symbolizer.hpp>

#include <mapnik/scale_denominator.hpp>


#include <mapnik/symbolizer.hpp>
#include <mapnik/text_symbolizer.hpp>

// boost
#include <boost/shared_ptr.hpp>

#include <mapnik/shield_symbolizer.hpp>

#include <mapnik/point_symbolizer.hpp>

#include <mapnik/polygon_symbolizer.hpp>


// // mapnik
 #include <mapnik/value.hpp>
 #include <mapnik/expression_node.hpp>


#include <mapnik/path_expression_grammar.hpp>
#include <mapnik/placement_finder.hpp>

#include <mapnik/label_collision_detector.hpp>
#include <mapnik/line_pattern_symbolizer.hpp>
#include <mapnik/line_symbolizer.hpp>
#include <mapnik/markers_symbolizer.hpp>
#include <mapnik/polygon_pattern_symbolizer.hpp>

#include <mapnik/attribute_collector.hpp>

#include <mapnik/rule.hpp>

#include <mapnik/feature_type_style.hpp> // needs attribute collector

#ifdef HAVE_CONFIG_H
   #include <config.h>
#endif

// // mapnik
#include <mapnik/enumeration.hpp>
#include <mapnik/feature_type_style.hpp>

#include <mapnik/map.hpp> // needs  feature_type_style.hpp



#ifdef MAPNIK_DEBUG
//#include <mapnik/wall_clock_timer.hpp>
#endif
#include <mapnik/expression_evaluator.hpp>
#include <mapnik/feature_style_processor.hpp>


// png stuff
#include <mapnik/image_util.hpp>
#include <mapnik/png_io.hpp>
#include <mapnik/jpeg_io.hpp>

#endif
