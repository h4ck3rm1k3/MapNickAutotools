
libmapnikdir = $(pkgincludedir)

if HAVE_LIBXML2
libxml2_inc = \
	libxml2_loader.hpp
endif

if HAVE_CAIRO
cairo_inc = \
	cairo_renderer.hpp
endif


libmapnik_HEADERS = \
	agg_renderer.hpp          feature_factory.hpp           layer.hpp                       quad_tree.hpp\
arrow.hpp                 feature.hpp                   libxml2_loader.hpp              query.hpp									  \
attribute_collector.hpp   feature_layer_desc.hpp        line_pattern_symbolizer.hpp     raster.hpp									  \
attribute_descriptor.hpp  feature_style_processor.hpp   line_symbolizer.hpp             raster_symbolizer.hpp								  \
box2d.hpp                 feature_type_style.hpp        load_map.hpp                    rule.hpp									  \
cairo_renderer.hpp        fill.hpp                      map.hpp                         save_map.hpp									  \
color_factory.hpp         filter_factory.hpp            markers_converter.hpp           scale_denominator.hpp								  \
color.hpp                 filter_featureset.hpp         markers_symbolizer.hpp          shield_symbolizer.hpp								  \
config_error.hpp          font_engine_freetype.hpp      memory_datasource.hpp           stroke.hpp									  \
config.hpp                font_set.hpp                  memory_featureset.hpp           style_factory.hpp								  \
coord_array.hpp           gamma.hpp                     memory.hpp                      style.hpp									  \
coord.hpp                 geometry.hpp                  octree.hpp                      symbolizer.hpp									  \
css_color_grammar.hpp     geom_util.hpp                 params.hpp                      text_path.hpp									  \
ctrans.hpp                global.hpp                    path_expression_grammar.hpp     text_symbolizer.hpp								  \
datasource_cache.hpp      graphics.hpp                  placement_finder.hpp            unicode.hpp									  \
datasource.hpp            hit_test_filter.hpp           plugin.hpp                      utils.hpp									  \
distance.hpp              image_cache.hpp               png_io.hpp                      value.hpp									  \
ellipsoid.hpp             image_data.hpp                point_symbolizer.hpp            version.hpp									  \
enumeration.hpp           image_reader.hpp              polygon_pattern_symbolizer.hpp  vertex.hpp									  \
expression_evaluator.hpp  image_util.hpp                polygon_symbolizer.hpp          vertex_transform.hpp								  \
expression_grammar.hpp    image_view.hpp                pool.hpp                        vertex_vector.hpp								  \
expression_node.hpp       jpeg_io.hpp                   projection.hpp                  wall_clock_timer.hpp								  \
expression_string.hpp     label_collision_detector.hpp  proj_transform.hpp              wkb.hpp factory.hpp               label_placement.hpp           ptree_helpers.hpp


EXTRA_DIST = \
	$(libmapnik_HEADERS)

## File created by the gnome-build tools

