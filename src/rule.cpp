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

}
