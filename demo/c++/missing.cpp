#include <mapnik/stdinc.hpp>

namespace mapnik 
{


template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append(mapnik::line_symbolizer const&)
{

}

template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append(mapnik::polygon_symbolizer const&)
{

}

template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append(mapnik::text_symbolizer const&)
{

}

template <> template <>
mapnik::feature_style_processor<mapnik::agg_renderer<mapnik::image_32> >::apply_to_layer(mapnik::layer const&, mapnik::agg_renderer<mapnik::image_32>&, mapnik::projection const&, double)
{

}


}


icu_4_0::UnicodeString::UnicodeString(icu_4_0::UnicodeString const&)
{

}
