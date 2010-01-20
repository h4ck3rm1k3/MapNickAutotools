#include <mapnik/stdinc.hpp>
#include <mapnik/agg_renderer.hpp>

namespace mapnik 
{

template <class T> 
void mapnik::feature_style_processor< T>::apply_to_layer(mapnik::layer const&, T &, mapnik::projection const&, double)
{};



template <> 
void mapnik::feature_style_processor< mapnik::agg_renderer<mapnik::image_32> >::apply_to_layer(mapnik::layer const&, mapnik::agg_renderer<mapnik::image_32> &, mapnik::projection const&, double)
{};


  // explicit
template class  feature_style_processor< mapnik::agg_renderer<mapnik::image_32> >;


}
