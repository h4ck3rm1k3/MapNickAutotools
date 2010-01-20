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


template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append<mapnik::markers_symbolizer>(mapnik::markers_symbolizer const&)

{

}

template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append<mapnik::point_symbolizer>(mapnik::point_symbolizer const&)

{
}


template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append<mapnik::line_pattern_symbolizer>(mapnik::line_pattern_symbolizer const&)
{
}

template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append<mapnik::polygon_pattern_symbolizer>(mapnik::polygon_pattern_symbolizer const&)
{
}

template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append<mapnik::shield_symbolizer>(mapnik::shield_symbolizer const&)
{
}

template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append<mapnik::building_symbolizer>(mapnik::building_symbolizer const&)
{
}

template <> template <>
void mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::append<mapnik::raster_symbolizer>(mapnik::raster_symbolizer const&)
{
}


}
