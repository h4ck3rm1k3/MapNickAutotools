
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

#include <iostream>
#include "shape_featureset.hpp"

template <typename filterT>
shape_featureset<filterT>::shape_featureset(const filterT& filter, 
                                            const std::string& shape_file,
                                            const std::set<std::string>& attribute_names,
                                            std::string const& encoding,
                                            long file_length )
   : filter_(filter),
     shape_type_(shape_io::shape_null),
     shape_(shape_file),
     query_ext_(),
     tr_(new transcoder(encoding)),
     file_length_(file_length),
     count_(0)
{
   shape_.shp().skip(100);
   //attributes
   typename std::set<std::string>::const_iterator pos=attribute_names.begin();
   while (pos!=attribute_names.end())
   {
      for (int i=0;i<shape_.dbf().num_fields();++i)
      {
         if (shape_.dbf().descriptor(i).name_ == *pos)
         {
            attr_ids_.push_back(i);
            break;
         }
      }
      ++pos;
   }
}


template <typename filterT>
feature_ptr shape_featureset<filterT>::next()
{
   
   using mapnik::point_impl;
   std::streampos pos=shape_.shp().pos();
   
   if (pos < std::streampos(file_length_ * 2))
   {
      shape_.move_to(pos);
      int type=shape_.type();
      feature_ptr feature(new Feature(shape_.id_));
      if (type == shape_io::shape_point)
      {
         double x=shape_.shp().read_double();
         double y=shape_.shp().read_double();
         geometry2d * point = new point_impl;
         point->move_to(x,y);
         feature->add_geometry(point);
         ++count_;
      }
      else if (type == shape_io::shape_pointm)
      {
         double x=shape_.shp().read_double();
         double y=shape_.shp().read_double();
         shape_.shp().read_double();//m
         geometry2d * point = new point_impl;
         point->move_to(x,y);
         feature->add_geometry(point);
         ++count_;
      }
      else if (type == shape_io::shape_pointz)
      {
         double x=shape_.shp().read_double();
         double y=shape_.shp().read_double();
         shape_.shp().read_double();//z
         shape_.shp().read_double();//m
         geometry2d * point=new point_impl;
         point->move_to(x,y);
         feature->add_geometry(point);
         ++count_;
      }
      else
      {
         while (!filter_.pass(shape_.current_extent()))
         {	
            unsigned reclen=shape_.reclength_;
            if (!shape_.shp().is_eof())
            {
               long pos = shape_.shp().pos();
               shape_.move_to(pos + 2 * reclen - 36);
            }
            else
            {
               return feature_ptr();

            }
         }
	    
         switch (type)
         {
	  
            case shape_io::shape_polyline:
            {
               geometry2d * line = shape_.read_polyline();
               feature->add_geometry(line);
               ++count_;
               break;
            }
            case shape_io::shape_polylinem:
            {
               geometry2d * line = shape_.read_polylinem();
               feature->add_geometry(line);
               ++count_;
               break;
            }
            case shape_io::shape_polylinez:
            {
               geometry2d * line = shape_.read_polylinez();
               feature->add_geometry(line);
               ++count_;
               break;
            }
            case shape_io::shape_polygon:
            {		 
               geometry2d * poly = shape_.read_polygon();
               feature->add_geometry(poly);
               ++count_;
               break;
            }
            case shape_io::shape_polygonm:
            {		 
               geometry2d * poly = shape_.read_polygonm();
               feature->add_geometry(poly);
               ++count_;
               break;
            }
            case shape_io::shape_polygonz:
            {
               geometry2d * poly = shape_.read_polygonz();
               feature->add_geometry(poly);
               ++count_;
               break;
            }

         }
      }
      if (attr_ids_.size())
      {
         shape_.dbf().move_to(shape_.id_);
         std::vector<int>::const_iterator pos=attr_ids_.begin();
         std::vector<int>::const_iterator end=attr_ids_.end();
         
         while (pos!=end)
         {
            try 
            {
               shape_.dbf().add_attribute(*pos,*tr_,*feature);//TODO optimize!!!
            }
            catch (...)
            {
               std::clog << "error processing attributes " << std::endl;
            }
            ++pos;
         }
      }
      return feature;
   }
   else
   {
#ifdef MAPNIK_DEBUG
      std::clog<<" total shapes read="<<count_<<"\n";
#endif
      return feature_ptr();
   }
}


template <typename filterT>
shape_featureset<filterT>::~shape_featureset() {}

template class shape_featureset<mapnik::filter_in_box>;
template class shape_featureset<mapnik::filter_at_point>;

         
