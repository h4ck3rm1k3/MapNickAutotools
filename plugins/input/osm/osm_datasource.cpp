/*****************************************************************************
 * 
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2006 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/
#include <mapnik/stdinc.hpp>
/*
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <mapnik/geom_util.hpp>
#include <mapnik/query.hpp>
#include <set>
*/

#include "osm_datasource.hpp"
#include "osm_featureset.hpp"
#include "dataset_deliverer.h"
#include "osmtagtypes.h"
#include "osmparser.h"

DATASOURCE_PLUGIN(osm_datasource)

using mapnik::String;
using mapnik::Double;
using mapnik::Integer;
using mapnik::datasource_exception;
using mapnik::filter_in_box;
using mapnik::filter_at_point;
using mapnik::attribute_descriptor;

const std::string osm_datasource::name_ = "osm";

osm_datasource::osm_datasource(const parameters &params)
   : datasource (params),
     type_(datasource::Vector),
     desc_(*params.get<std::string>("type"), *params.get<std::string>("encoding","utf-8")) 
{
    osm_data_ = NULL;
    std::string osm_filename= *params.get<std::string>("file","");
    std::string parser = *params.get<std::string>("parser","libxml2");
    std::string url = *params.get<std::string>("url","");
    std::string bbox = *params.get<std::string>("bbox","");

    bool do_process=false;

    // load the data
    // if we supplied a filename, load from file
    if (url!="" && bbox!="")
    {
        // otherwise if we supplied a url and a bounding box, load from the url
#ifdef MAPNIK_DEBUG
		cerr<<"loading_from_rul: url="<<url << " bbox="<<bbox<<endl;
#endif
        if((osm_data_=dataset_deliverer::load_from_url
            (url,bbox,parser))==NULL)    
        {
            throw datasource_exception("Error loading from URL");
        }
        do_process=true;
    }
    else if(osm_filename!="")
    {
        if ((osm_data_=
            dataset_deliverer::load_from_file(osm_filename,parser))==NULL)
        {
            throw datasource_exception("Error loading from file");
        }    
        do_process=true;
    }

    if(do_process==true)
    {
        osm_tag_types tagtypes;
        tagtypes.add_type("maxspeed",mapnik::Integer);
        tagtypes.add_type("z_order",mapnik::Integer);

        osm_data_->rewind();
        // Need code to get the attributes of all the data
        std::set<std::string> keys= osm_data_->get_keys();

        // Add the attributes to the datasource descriptor - assume they are
        // all of type String
        for(std::set<std::string>::iterator i=keys.begin(); i!=keys.end(); i++)
          desc_.add_descriptor(attribute_descriptor(*i,tagtypes.get_type(*i)));

        // Get the bounds of the data and set extent_ accordingly
        bounds b = osm_data_->get_bounds();
        extent_ =  box2d<double>(b.w,b.s,b.e,b.n);
    }
}


osm_datasource::~osm_datasource() 
{ 
    // Do not do as is now static variable and cleaned up at exit
    //delete osm_data_; 
}


int osm_datasource::type() const
{
   return type_;
}

layer_descriptor osm_datasource::get_descriptor() const
{
   return desc_;
}

featureset_ptr osm_datasource::features(const query& q) const
{
   filter_in_box filter(q.get_bbox());
    // so we need to filter osm features by bbox here...
    
    return featureset_ptr
         (new osm_featureset<filter_in_box>(filter,
                                              osm_data_,
                                              q.property_names(),
                                              desc_.get_encoding()));
}

featureset_ptr osm_datasource::features_at_point(coord2d const& pt) const
{
   filter_at_point filter(pt);
   // collect all attribute names
   std::vector<attribute_descriptor> const& desc_vector = 
        desc_.get_descriptors();
   std::vector<attribute_descriptor>::const_iterator itr = desc_vector.begin();
   std::vector<attribute_descriptor>::const_iterator end = desc_vector.end();
   std::set<std::string> names;
    
   while (itr != end)
   {    
      names.insert(itr->get_name());
      ++itr;
   }
    
    return featureset_ptr
         (new osm_featureset<filter_at_point>(filter,
                                                osm_data_,
                                                names,
                                                desc_.get_encoding()));
}

box2d<double> osm_datasource::envelope() const
{
   return extent_;
}
