#include <mapnik/stdinc.hpp>
#include <mapnik/agg_renderer.hpp>

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

template <class T> 
void mapnik::feature_style_processor< T>::apply_to_layer(mapnik::layer const&, T &, mapnik::projection const&, double)
{};

template <> 
void mapnik::feature_style_processor< mapnik::agg_renderer<mapnik::image_32> >::apply_to_layer(mapnik::layer const&, mapnik::agg_renderer<mapnik::image_32> &, mapnik::projection const&, double)
{};

/*



typedef mapnik::agg_renderer<mapnik::image_32> T1;
template <> template <>
void mapnik::feature_style_processor<T1 >::apply_to_layer(
						mapnik::layer const& lay, 
						T1 & p, 
						mapnik::projection const& proj0,
						double scale_denom)
{

}
*/

}

/*mapnik::feature_style_processor<mapnik::agg_renderer<mapnik::image_32> >::apply_to_layer(mapnik::layer const&, mapnik::agg_renderer<mapnik::image_32>&, mapnik::projection const&, double)
{

}*/

