/*****************************************************************************
 * 
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2006 Artem Pavlenko, Jean-Francois Doyon
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

extern "C"
{
#include <png.h>
}

// boost
#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
// mapnik
#include <mapnik/graphics.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/jpeg_io.hpp>
#include <mapnik/png_io.hpp>
#include <mapnik/image_reader.hpp>
#include <sstream>
// cairo
#if defined(HAVE_CAIRO) && defined(HAVE_PYCAIRO)
#include <cairomm/surface.h>
#include <pycairo.h>
#endif

using mapnik::image_32;
using mapnik::image_reader;
using mapnik::get_image_reader;
using mapnik::type_from_filename;
using namespace boost::python;
using mapnik::save_to_file;

// output 'raw' pixels
PyObject* tostring1( image_32 const& im)
{
    int size = im.width() * im.height() * 4;
    return ::PyString_FromStringAndSize((const char*)im.raw_data(),size);
}

// encode (png,jpeg)
PyObject* tostring2(image_32 const & im, std::string const& format)
{
   std::string s = save_to_string(im, format);
   return ::PyString_FromStringAndSize(s.data(),s.size());
}

void (*save_to_file1)( mapnik::image_32 const&, std::string const&,std::string const&) = mapnik::save_to_file;
void (*save_to_file2)( mapnik::image_32 const&, std::string const&) = mapnik::save_to_file;

boost::shared_ptr<image_32> open_from_file(std::string const& filename)
{
    boost::optional<std::string> type = type_from_filename(filename);
    if (type)
    {
	std::auto_ptr<image_reader> reader(get_image_reader(filename,*type));
	if (reader.get())
	{
	    boost::shared_ptr<image_32> image_ptr(new image_32(reader->width(),reader->height()));
	    reader->read(0,0,image_ptr->data());
	    return image_ptr;
	}
	throw mapnik::image_reader_exception("Failed to load: " + filename);  
    }
    throw mapnik::image_reader_exception("Unsupported image format:" + filename);
}
    
void blend (image_32 & im, unsigned x, unsigned y, image_32 const& im2, float opacity)
{
   im.set_rectangle_alpha2(im2.data(),x,y,opacity);
}

#if defined(HAVE_CAIRO) && defined(HAVE_PYCAIRO)
boost::shared_ptr<image_32> from_cairo(PycairoSurface* surface)
{
    Cairo::RefPtr<Cairo::ImageSurface> s(new Cairo::ImageSurface(surface->surface));
    boost::shared_ptr<image_32> image_ptr(new image_32(s));
    return image_ptr;
}
#endif

void export_image()
{
    using namespace boost::python;
    class_<image_32,boost::shared_ptr<image_32> >("Image","This class represents a 32 bit RGBA image.",init<int,int>())
       .def("width",&image_32::width)
       .def("height",&image_32::height)
       .def("view",&image_32::get_view)
       .add_property("background",make_function
                     (&image_32::get_background,return_value_policy<copy_const_reference>()),
                     &image_32::set_background, "The background color of the image.")
       .def("blend",&blend)
       .def("tostring",&tostring1)
       .def("tostring",&tostring2)
       .def("save", save_to_file1)
       .def("save", save_to_file2)
       .def("open",open_from_file)
       .staticmethod("open")
#if defined(HAVE_CAIRO) && defined(HAVE_PYCAIRO)
       .def("from_cairo",&from_cairo)
       .staticmethod("from_cairo")
#endif
       ;    
    
}
