
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
	agg_renderer.hpp                     layer.hpp                       quad_tree.hpp\
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
GCH_FILES= unicode.hpp.gch value.hpp.gch feature.hpp.gch  layer.hpp.gch   quad_tree.hpp.gch   arrow.hpp.gch      libxml2_loader.hpp.gch   query.hpp.gch   attribute_collector.hpp.gch   feature_layer_desc.hpp.gch   line_pattern_symbolizer.hpp.gch   raster.hpp.gch   attribute_descriptor.hpp.gch   feature_style_processor.hpp.gch   line_symbolizer.hpp.gch   raster_symbolizer.hpp.gch   box2d.hpp.gch   feature_type_style.hpp.gch   load_map.hpp.gch   rule.hpp.gch   cairo_renderer.hpp.gch   fill.hpp.gch   map.hpp.gch   save_map.hpp.gch   color_factory.hpp.gch   filter_factory.hpp.gch   markers_converter.hpp.gch   scale_denominator.hpp.gch   color.hpp.gch   filter_featureset.hpp.gch   markers_symbolizer.hpp.gch   shield_symbolizer.hpp.gch   config_error.hpp.gch   font_engine_freetype.hpp.gch   memory_datasource.hpp.gch   stroke.hpp.gch   config.hpp.gch   font_set.hpp.gch   memory_featureset.hpp.gch   style_factory.hpp.gch   coord_array.hpp.gch   gamma.hpp.gch   memory.hpp.gch   style.hpp.gch   coord.hpp.gch   geometry.hpp.gch   octree.hpp.gch   symbolizer.hpp.gch   css_color_grammar.hpp.gch   geom_util.hpp.gch   params.hpp.gch   text_path.hpp.gch   ctrans.hpp.gch   global.hpp.gch   path_expression_grammar.hpp.gch   text_symbolizer.hpp.gch   datasource_cache.hpp.gch   graphics.hpp.gch   placement_finder.hpp.gch      datasource.hpp.gch   hit_test_filter.hpp.gch   plugin.hpp.gch   utils.hpp.gch   distance.hpp.gch   image_cache.hpp.gch   png_io.hpp.gch      ellipsoid.hpp.gch   image_data.hpp.gch   point_symbolizer.hpp.gch   version.hpp.gch   enumeration.hpp.gch   image_reader.hpp.gch   polygon_pattern_symbolizer.hpp.gch   vertex.hpp.gch   expression_evaluator.hpp.gch   image_util.hpp.gch   polygon_symbolizer.hpp.gch   vertex_transform.hpp.gch   expression_grammar.hpp.gch   image_view.hpp.gch   pool.hpp.gch   vertex_vector.hpp.gch   expression_node.hpp.gch   jpeg_io.hpp.gch   projection.hpp.gch   wall_clock_timer.hpp.gch   expression_string.hpp.gch   label_collision_detector.hpp.gch   proj_transform.hpp.gch   wkb.hpp.gch   factory.hpp.gch   label_placement.hpp.gch   ptree_helpers.hpp.gch  ptree_helpers.hpp.gch stdinc.hpp.gch agg_renderer.hpp.gch 




BUILT_SOURCES = report.txt $(GCH_FILES) $(patsubst %.hpp, %.hpp.gch ,$(libmapnik_HEADERS))


#BUILT_SOURCES = $(subst .hpp, hpp.gch ,	$(libmapnik_HEADERS))

report :
	ls *.hpp

report.txt:
	ls *.hpp > report.txt
	echo test $(subst .hpp, hpp.gch ,	$(libmapnik_HEADERS))
	echo headers $(libmapnik_HEADERS)
	echo TEST $(patsubst %.hpp, %.hpp.gch ,$(libmapnik_HEADERS))

CLEANFILES =$(GCH_FILES)

%.hpp.gch: %.hpp
	$(CXX) -save-temps  -I ../.. -I .. -I  	${PROFILING_CFLAGS} \
	${TRACING_CFLAGS} \
	${PNG_CFLAGS} \
	${FREETYPE2_CFLAGS} \
	${AGG_CFLAGS} \
	${BOOST_CPPFLAGS} \
	${LIBXML2_CFLAGS} \
	${CAIRO_CFLAGS} -c $< 

# ${JPEG_CFLAGS} 
# ${TIFF_CFLAGS} 
# ${PROJ_CFLAGS} 
# ${LTDL_CFLAGS} 

cleangch :
	rm $(GCH_FILES)