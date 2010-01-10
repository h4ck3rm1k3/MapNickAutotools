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
//$Id$

//mapnik
#include <mapnik/symbolizer.hpp>

namespace mapnik {

symbolizer_with_image::symbolizer_with_image(path_expression_ptr file)
    : image_filename_( file ) {}

symbolizer_with_image::symbolizer_with_image( symbolizer_with_image const& rhs)
    : image_filename_(rhs.image_filename_) {}
   

path_expression_ptr symbolizer_with_image::get_filename() const
{
    return image_filename_;
}

void symbolizer_with_image::set_filename(path_expression_ptr image_filename) 
{
    image_filename_ = image_filename;
}
      
} // end of namespace mapnik



