#include <mapnik/stdinc.hpp>
#include <mapnik/agg_renderer.hpp>

namespace mapnik 
{

template <class T> 
void mapnik::feature_style_processor< T>::apply_to_layer(mapnik::layer const&, T &, mapnik::projection const&, double)
{
  std::cerr << "TODO! void mapnik::feature_style_processor< T>::apply_to_layer(mapnik::layer const&, T &, mapnik::projection const&, double)" << std::endl;
};


  // TODO: new stub
// operator
template <>
void mapnik::attribute_collector::operator()
<mapnik::rule<
   mapnik::feature<
     mapnik::geometry<
       mapnik::vertex<
	 double, 2> >, boost::shared_ptr<mapnik::raster> > > >
(
 mapnik::rule<
 mapnik::feature<
 mapnik::geometry<
 mapnik::vertex<double, 2> 
 >, 
 

 boost::shared_ptr<mapnik::raster> > 
   > const& sym )
{

}

class symbolizer_base2
{
public:

  //U void mapnik::agg_renderer<mapnik::image_32>::process<mapnik::symbolizer_base2>(mapnik::symbolizer_base2 const&, mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > const&, mapnik::proj_transform const&)


  //template <class Processor> 
  virtual void symbol_dispatch (
			mapnik::agg_renderer<mapnik::image_32>&  output,
			Feature const& f, 
			proj_transform const& prj_trans) const =0;
  //  {
  //  process(output,f,prj_trans);
  //}
  // virtual void process(	mapnik::agg_renderer<mapnik::image_32>&  output,
  // 		   Feature const& f, 
  // 			proj_transform const& prj_trans) const =0;
  // template<typename Visitor> 
  // typename Visitor::result_type 
  // apply_visitor(const Visitor & ) const;

  // template<typename Visitor, typename Variant> 
  // typename Visitor::result_type 
  // apply_visitor(Visitor & visitor, Variant & operand);


  // template<typename Visitor, typename Variant> 
  // typename Visitor::result_type 
  // apply_visitor(const Visitor & visitor, Variant & operand);


  // template<typename BinaryVisitor, typename Variant1, typename Variant2> 
  // typename BinaryVisitor::result_type 
  // apply_visitor(BinaryVisitor & visitor, Variant1 & operand1, 
  //               Variant2 & operand2);


  // template<typename BinaryVisitor, typename Variant1, typename Variant2> 
  // typename BinaryVisitor::result_type 
  // apply_visitor(const BinaryVisitor & visitor, Variant1 & operand1, 
  //               Variant2 & operand2);

};


// // apply visitor
// template <>
// mapnik::feature_style_processor<mapnik::agg_renderer<mapnik::image_32> >::symbol_dispatch::result_type 
// mapnik::symbolizer_base2::apply_visitor<
//   mapnik::feature_style_processor<    mapnik::agg_renderer<      mapnik::image_32>     >
//   ::symbol_dispatch
//   >
// (
//  mapnik::feature_style_processor<mapnik::agg_renderer<mapnik::image_32> >::symbol_dispatch const&) const
// {
  
// }


// get the symbolizers
template <> template <>
std::vector<mapnik::symbolizer_base2, std::allocator<mapnik::symbolizer_base2> > const& 
mapnik::rule<mapnik::feature<mapnik::geometry<mapnik::vertex<double, 2> >, boost::shared_ptr<mapnik::raster> > >::
get_symbolizers
<std::vector<mapnik::symbolizer_base2, std::allocator<mapnik::symbolizer_base2> > >
() const
{
}


typedef std::vector<symbolizer_base2> rule_type_symbolizers;
typedef const rule_type_symbolizers & rule_type_symbolizers2;

template <> 
void mapnik::feature_style_processor< mapnik::agg_renderer<mapnik::image_32> >::
apply_to_layer(
	       mapnik::layer const& lay,
	       mapnik::agg_renderer<mapnik::image_32> & p,
	       mapnik::projection const& proj0, 
	       double scale_denom)
{
  //  std::cerr << "TODO! void mapnik::feature_style_processor< mapnik::agg_renderer<mapnik::image_32> >::apply_to_layer(mapnik::layer const&, mapnik::agg_renderer<mapnik::image_32> &, mapnik::projection const&, double)" << std::endl;

#ifdef MAPNIK_DEBUG
	//wall_clock_progress_timer timer(clog, "end layer rendering: ");
#endif
  p.start_layer_processing(lay);
	PlugIn::datasource_ptr ds=lay.datasource();
	if (ds)
	{
	    box2d<double> ext = m_.get_buffered_extent();
	    projection proj1(lay.srs());
	    proj_transform prj_trans(proj0,proj1);
               
	    double mx0 = ext.minx();
	    double my0 = ext.miny();
	    double mz0 = 0.0;
	    double mx1 = ext.maxx();
	    double my1 = ext.maxy();
	    double mz1 = 0.0;
               
	    // project main map projection into layers extent
	    prj_trans.forward(mx0,my0,mz0);
	    prj_trans.forward(mx1,my1,mz1);

	    // if no intersection then nothing to do for layer
	    box2d<double> layer_ext = lay.envelope();
	    if ( mx0 > layer_ext.maxx() || mx1 < layer_ext.minx() || my0 > layer_ext.maxy() || my1 < layer_ext.miny() )
	    {
		return;
	    }
               
	    // clip query bbox
	    mx0 = std::max(layer_ext.minx(),mx0);
	    my0 = std::max(layer_ext.miny(),my0);
	    mx1 = std::min(layer_ext.maxx(),mx1);
	    my1 = std::min(layer_ext.maxy(),my1);
               
	    box2d<double> bbox(mx0,my0,mx1,my1);
               
      double resolution = m_.getWidth()/bbox.width();
      query q(bbox,resolution,scale_denom); //BBOX query
               
	    std::vector<std::string> const& style_names = lay.styles();
	    std::vector<std::string>::const_iterator stylesIter = style_names.begin();
	    std::vector<std::string>::const_iterator stylesEnd = style_names.end(); 
	    for (;stylesIter != stylesEnd; ++stylesIter)
	    {
		std::set<std::string> names;
		attribute_collector collector(names);
		std::vector<rule_type*> if_rules;
		std::vector<rule_type*> else_rules;
                    
		bool active_rules=false;
                  
		boost::optional<feature_type_style const&> style=m_.find_style(*stylesIter);
		if (!style) continue;
                  
		const std::vector<rule_type>& rules=(*style).get_rules();
		std::vector<rule_type>::const_iterator ruleIter=rules.begin();
		std::vector<rule_type>::const_iterator ruleEnd=rules.end();
                                        
		for (;ruleIter!=ruleEnd;++ruleIter)
		{
		    if (ruleIter->active(scale_denom))
		    {
                        active_rules=true;
			// collect unique attribute names
			collector(*ruleIter);
			if (ruleIter->has_else_filter())
                        {
			    else_rules.push_back(const_cast<rule_type*>(&(*ruleIter)));
                        }
                        else
                        {
			    if_rules.push_back(const_cast<rule_type*>(&(*ruleIter))); 		    
                        }
		    }
		}
		std::set<std::string>::const_iterator namesIter=names.begin();
		std::set<std::string>::const_iterator namesEnd =names.end();
                    
		// push all property names
		for (;namesIter!=namesEnd;++namesIter)
		{
		    q.add_property_name(*namesIter);
		}
		if (active_rules)
		{
		    featureset_ptr fs=ds->features(q);
		    if (fs)
		    {   	    
                        feature_ptr feature;
                        while ((feature = fs->next()))
                        {		   
			    bool do_else=true;		    
			    std::vector<rule_type*>::const_iterator itr=if_rules.begin();
			    std::vector<rule_type*>::const_iterator end=if_rules.end();
			    for (;itr != end;++itr)
			    {
				expression_ptr const& expr=(*itr)->get_filter();    
				//				value_type result = *expr.evaluate<Feature,value_type>(*feature);
 				value_type result = boost::apply_visitor(evaluate<Feature,value_type>(*feature),*expr);
				if (result.to_bool())
				{   
				  do_else=false;
				  
				  //const rule_type_symbolizers& symbols 
				  const rule_type_symbolizers&  symbols = (*itr)->get_symbolizers<rule_type_symbolizers>();
				  rule_type_symbolizers::const_iterator symIter=symbols.begin();
				  rule_type_symbolizers::const_iterator symEnd =symbols.end();
				  for (;symIter != symEnd;++symIter)
				    {   
				      //boost::apply_visitor
				      symIter->symbol_dispatch(p,*feature,prj_trans);
				    }
				}			    
			    }
			    if (do_else)
			    {
				//else filter
				std::vector<rule_type*>::const_iterator itr=
				    else_rules.begin();
				std::vector<rule_type*>::const_iterator end=
				    else_rules.end();
				for (;itr != end;++itr)
				  {
				    const rule_type_symbolizers& symbols = (*itr)->get_symbolizers<rule_type_symbolizers>();
				    rule_type_symbolizers::const_iterator symIter= symbols.begin();
				    rule_type_symbolizers::const_iterator symEnd = symbols.end();
				    
				    for (;symIter!=symEnd;++symIter)
				      {
					//boost::apply_visitor
					symIter->symbol_dispatch(p,*feature,prj_trans);
				      } 				  
				  }
			    }	  
                        }
		    }
		}
	    }               
	}
	p.end_layer_processing(lay);
    }	

};

  // explicit
//template class  feature_style_processor< mapnik::agg_renderer<mapnik::image_32> >;
