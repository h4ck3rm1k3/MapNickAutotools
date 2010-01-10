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
//$Id: image_reader.cpp 17 2005-03-08 23:58:43Z pavlenko $

#include <mapnik/image_reader.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/factory.hpp>

namespace mapnik
{  
typedef factory<image_reader,std::string, 
		image_reader* (*)(const std::string&)>  ImageReaderFactory;
    
    
bool register_image_reader(const std::string& type,image_reader* (* fun)(const std::string&))
{
    return ImageReaderFactory::instance()->register_product(type,fun);
}
    
image_reader* get_image_reader(const std::string& filename,const std::string& type) 
{
    return ImageReaderFactory::instance()->create_object(type,filename);
}

image_reader* get_image_reader(const std::string& filename) 
{
    boost::optional<std::string> type = type_from_filename(filename);
    if (type)
    {
	return ImageReaderFactory::instance()->create_object(*type,filename);
    }
    return 0;
}

}
