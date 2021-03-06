#include <mapnik/stdinc.hpp>
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
#include<fstream>
//#include <mapnik/png_io.hpp>

//$Id: image_util.cpp 36 2005-04-05 14:32:18Z pavlenko $

/*extern "C"
{
#include <png.h>
}

// mapnik

#include <mapnik/graphics.hpp>
#include <mapnik/memory.hpp>
#include <mapnik/image_view.hpp>

// stl
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
*/


namespace mapnik
{    
    template <typename T>
    std::string save_to_string(T const& image,
                               std::string const& type)
    {
        std::ostringstream ss(std::ios::out|std::ios::binary);
        //all this should go into image_writer factory
        if (type=="png")  save_as_png(ss,image);
        else if (type == "png256") save_as_png256(ss,image);
        else if (boost::algorithm::istarts_with(type,std::string("jpeg")))
        {
            int quality = 85;
            try 
            {
                if(type.substr(4).length() != 0)
                {
                    quality = boost::lexical_cast<int>(type.substr(4));
                    if(quality<1 || quality>100)
                        throw ImageWriterException("invalid jpeg quality: " + type.substr(4));
                }
                save_as_jpeg(ss,quality,image); 
            } 
            catch(boost::bad_lexical_cast &)
            {
                throw ImageWriterException("invalid jpeg quality: " + type.substr(4));
            }
        }
        else throw ImageWriterException("unknown file type: " + type);
        return ss.str();
    }

  void test(std::string const& filename)
  {
    std::ofstream afile (filename.c_str(), std::ios::out| std::ios::trunc|std::ios::binary);
    if (afile)
      {

      }
  }
    template <typename T>
    void save_to_file(T const& image,
                      std::string const& filename,
                      std::string const& type)
    {
      // todo!

      
    std::ofstream afile (filename.c_str(), std::ios::out| std::ios::trunc|std::ios::binary);
    if (afile)
      {
	save_as_png(afile,image);
      }
   
        {
            //all this should go into image_writer factory
	  if (type=="png")  
	    {
	      save_as_png(afile,image);
	    }
	  //else if (type == "png256") save_as_png256(file,image);
	  /* else if (boost::algorithm::istarts_with(type,std::string("jpeg")))
            {
                int quality = 85;
                try 
                {
                    if(type.substr(4).length() != 0)
                    {
                        quality = boost::lexical_cast<int>(type.substr(4));
                        if(quality<0 || quality>100)
                            throw ImageWriterException("invalid jpeg quality: " + type.substr(4) + " out of bounds");
                    }
                    save_as_jpeg(file,quality,image); 
                } 
                catch(boost::bad_lexical_cast &)
                {
                    throw ImageWriterException("invalid jpeg quality: " + type.substr(4) + " not a number");
                }
	  */
	  else throw ImageWriterException("unknown file type: " + type);
        }
      
    }
	
    template <typename T>
    void save_to_file(T const& image,std::string const& filename)
    {
	boost::optional<std::string> type = type_from_filename(filename);
	if (type)
	{
	    save_to_file<T>(image,filename,*type);
	}
    }
     

    template void save_to_file<image_data_32>(image_data_32 const&,
                                            std::string const&,
                                            std::string const&);

    template void save_to_file<image_data_32>(image_data_32 const&,
                                            std::string const&);

    template std::string save_to_string<image_data_32>(image_data_32 const&,
                                                     std::string const&);

    template void save_to_file<image_view<image_data_32> > (image_view<image_data_32> const&,
                                                          std::string const&,
                                                          std::string const&);
   
    template void save_to_file<image_view<image_data_32> > (image_view<image_data_32> const&,
                                                          std::string const&);
   
    template std::string save_to_string<image_view<image_data_32> > (image_view<image_data_32> const&,
                                                                   std::string const&);


// template <> 

// void save_as_png< 
//   image_view<ImageData<unsigned int> > 
//   >(image_view<ImageData<unsigned int> > const& image, std::string const& file)
// {
//   std::cerr <<<  "void save_as_png< image_view<ImageData<unsigned int> > >(image_view<ImageData<unsigned int> > const&, std::string const&)" << std::endl;
//   save_as_png(file ,  image);
// }

// template <> 
// void save_as_png<mapnik::ImageData<unsigned int> >(mapnik::ImageData<unsigned int> const& image,  std::string const& file)
// {
//   std::cerr <<<  "void save_as_png<mapnik::ImageData<unsigned int> >(mapnik::ImageData<unsigned int> const&,  std::string const&)" << std::endl;
//   //  save_as_png(file ,  image);

// }


}
