#pragma once 

#include <algorithm>
#include <bitset>
#include <boost/algorithm/string.hpp>
#include <boost/concept_check.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/cstdint.hpp>
#include <boost/detail/endian.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
//#include <boost/fusion/include/adapt_class.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/optional/optional.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/regex.hpp>
#include <boost/regex/icu.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/utility.hpp>
#include <boost/variant.hpp>
#include <boost/version.hpp>

#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <cassert>
#include <cmath>
#include <config.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <ft2build.h>
//TODO:#include FT_FREETYPE_H
//#include FT_GLYPH_H
#include <functional>
#include <iomanip>
#include <iostream>
#include <jpeglib.h>
#include <limits>
#include <ltdl.h>
#include <map>

//#include <png.h>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/time.h> 
#include <unicode/ubidi.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/ushape.h>
#include <unicode/ustring.h>
#include <vector>



#include <mapnik/box2d.hpp>
#include <mapnik/color_factory.hpp>
#include <mapnik/color.hpp>
#include <mapnik/config_error.hpp>
#include <mapnik/config.hpp>
#include <mapnik/coord_array.hpp>
#include <mapnik/coord.hpp>
#include <mapnik/css_color_grammar.hpp>
#include <mapnik/ctrans.hpp>
#include <mapnik/datasource.hpp>
#include <mapnik/enumeration.hpp>
#include <mapnik/expression_evaluator.hpp>
#include <mapnik/expression_grammar.hpp>
#include <mapnik/expression_node.hpp>
#include <mapnik/feature_factory.hpp> // TODO remove
#include <mapnik/feature.hpp>
#include <mapnik/feature_layer_desc.hpp>


#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/font_set.hpp>
#include <mapnik/gamma.hpp>
#include <mapnik/geometry.hpp>
#include <mapnik/geom_util.hpp>
#include <mapnik/global.hpp>
#include <mapnik/graphics.hpp>
#include <mapnik/image_data.hpp>
#include <mapnik/image_view.hpp>
#include <mapnik/layer.hpp>

#include <mapnik/memory_datasource.hpp>
#include <mapnik/octree.hpp>
#include <mapnik/params.hpp>
#include <mapnik/plugin.hpp>
#include <mapnik/projection.hpp>
#include <mapnik/proj_transform.hpp>
#include <mapnik/quad_tree.hpp>
#include <mapnik/query.hpp>
#include <mapnik/raster.hpp>
#include <mapnik/stroke.hpp>


#include <mapnik/text_path.hpp>

#include <mapnik/unicode.hpp>
#include <mapnik/utils.hpp>
#include <mapnik/value.hpp>
#include <mapnik/vertex.hpp>
#include <mapnik/vertex_vector.hpp>

#include <mapnik/symbolizer.hpp>


#include <mapnik/feature_type_style.hpp>
#include <mapnik/map.hpp>
#include <mapnik/attribute_collector.hpp>
#include <mapnik/text_symbolizer.hpp>
#include <mapnik/raster_symbolizer.hpp>

#include <mapnik/scale_denominator.hpp>
#include <mapnik/shield_symbolizer.hpp>

#include <mapnik/point_symbolizer.hpp>

#include <mapnik/polygon_symbolizer.hpp>

#include <mapnik/path_expression_grammar.hpp>
#include <mapnik/placement_finder.hpp>

#include <mapnik/label_collision_detector.hpp>
#include <mapnik/line_pattern_symbolizer.hpp>
#include <mapnik/line_symbolizer.hpp>
#include <mapnik/markers_symbolizer.hpp>



#ifdef MAPNIK_DEBUG
//#include <mapnik/wall_clock_timer.hpp>
#endif
// // mapnik
// #include <mapnik/box2d.hpp>
// #include <mapnik/datasource.hpp>
// #include <mapnik/layer.hpp>
// #include <mapnik/map.hpp>
// #include <mapnik/attribute_collector.hpp>
// #include <mapnik/expression_evaluator.hpp>
// #include <mapnik/utils.hpp>
// #include <mapnik/projection.hpp>
// #include <mapnik/scale_denominator.hpp>
#include <mapnik/feature_style_processor.hpp>
#include <mapnik/polygon_pattern_symbolizer.hpp>


// #include <mapnik/line_symbolizer.hpp>
// #include <mapnik/line_pattern_symbolizer.hpp>
// #include <mapnik/polygon_symbolizer.hpp>
// #include <mapnik/polygon_pattern_symbolizer.hpp>
// #include <mapnik/point_symbolizer.hpp>
// #include <mapnik/raster_symbolizer.hpp>
// #include <mapnik/shield_symbolizer.hpp>
// #include <mapnik/text_symbolizer.hpp>
// #include <mapnik/markers_symbolizer.hpp>
// #include <mapnik/feature.hpp>
// #include <mapnik/expression_grammar.hpp>
// #include <boost/shared_ptr.hpp>
// #include <boost/variant.hpp>
// #include <string>
// #include <vector>
#include <mapnik/rule.hpp>

