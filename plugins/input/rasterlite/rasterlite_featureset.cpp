/*****************************************************************************
 * 
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2007 Artem Pavlenko
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
//$Id$

#include "rasterlite_featureset.hpp"

// mapnik
#include <mapnik/image_util.hpp>


using mapnik::query;
using mapnik::coord2d;
using mapnik::box2d;
using mapnik::Feature;
using mapnik::feature_ptr;
using mapnik::CoordTransform;
using mapnik::point_impl;
using mapnik::geometry2d;
using mapnik::query;



rasterlite_featureset::rasterlite_featureset(void* dataset, rasterlite_query q)
   : dataset_(dataset),
     gquery_(q),
     first_(true)
{
    rasterliteSetBackgroundColor(dataset_, 255, 0, 255);
    rasterliteSetTransparentColor(dataset_, 255, 0, 255);
}

rasterlite_featureset::~rasterlite_featureset()
{
#ifdef MAPNIK_DEBUG
   std::clog << "Rasterlite Plugin: closing dataset" << "\n";
#endif

   rasterliteClose(dataset_);
}

feature_ptr rasterlite_featureset::next()
{
   if (first_)
   {
      first_ = false;

      query *q = boost::get<query>(&gquery_);
      if(q) {
          return get_feature(*q);
      } else {
          coord2d *p = boost::get<coord2d>(&gquery_);
          if(p) {
              return get_feature_at_point(*p);
          }
      }
      // should never reach here
   }
   return feature_ptr();
}

feature_ptr rasterlite_featureset::get_feature(mapnik::query const& q)
{
#ifdef MAPNIK_DEBUG
   std::clog << "Rasterlite Plugin: get_feature" << "\n";
#endif

   feature_ptr feature(new Feature(1));

   double x0, y0, x1, y1;
   rasterliteGetExtent (dataset_, &x0, &y0, &x1, &y1);

   box2d<double> raster_extent(x0,y0,x1,y1); 
   box2d<double> intersect = raster_extent.intersect(q.get_bbox());

   int width = static_cast<int>(q.resolution() * intersect.width() + 0.5);
   int height = static_cast<int>(q.resolution() * intersect.height() + 0.5);

   double pixel_size = (intersect.width() >= intersect.height()) ?
       (intersect.width() / (double) width) : (intersect.height() / (double) height);

#ifdef MAPNIK_DEBUG         
   std::clog << "Rasterlite Plugin: Raster extent=" << raster_extent << "\n";
   std::clog << "Rasterlite Plugin: View extent=" << q.get_bbox() << "\n";
   std::clog << "Rasterlite Plugin: Intersect extent=" << intersect << "\n";
   std::clog << "Rasterlite Plugin: Query resolution=" << q.resolution() << "\n";
   std::clog << "Rasterlite Plugin: Size=" << width << " " << height << "\n";
   std::clog << "Rasterlite Plugin: Pixel Size=" << pixel_size << "\n";
#endif

   if (width > 0 && height > 0)
   {
      int size;
      void *raster;

      if (rasterliteGetRawImageByRect(dataset_,
            intersect.minx(), intersect.miny(), intersect.maxx(), intersect.maxy(),
            pixel_size, width, height, GAIA_RGBA_ARRAY, &raster, &size) == RASTERLITE_OK)
      {
          if (size > 0)
          {
              mapnik::image_data_32 image(width, height);
              image.set(0xffffffff);

              unsigned char* raster_data = static_cast<unsigned char*>(raster);
              unsigned char* image_data = image.getBytes();

              memcpy (image_data, raster_data, size);

              feature->set_raster(mapnik::raster_ptr(new mapnik::raster(intersect,image)));

              free (raster);

#ifdef MAPNIK_DEBUG         
              std::clog << "Rasterlite Plugin: Done" << "\n";
#endif
          }
          else
          {
#ifdef MAPNIK_DEBUG         
              std::clog << "Rasterlite Plugin: Error=" << rasterliteGetLastError (dataset_) << "\n";
#endif
          }
      }
      
      return feature;
   }
   return feature_ptr();
}


feature_ptr rasterlite_featureset::get_feature_at_point(mapnik::coord2d const& pt)
{
   return feature_ptr();
}

