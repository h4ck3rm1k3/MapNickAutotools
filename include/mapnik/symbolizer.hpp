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
//$Id: symbolizer.hpp 39 2005-04-10 20:39:53Z pavlenko $

#ifndef MAPNIK_SYMBOLIZER_HPP
#define MAPNIK_SYMBOLIZER_HPP

// mapnik
#include <mapnik/config.hpp>
#include <mapnik/path_expression_grammar.hpp>
#include <mapnik/symbolizer_base.hpp>


// // stl
// #include <string>
//#include "stdinc.hpp"
namespace mapnik 
{

  class symbolizer_with_image 
    : public              symbolizer_base

  {
public:
    path_expression_ptr get_filename() const;
    void set_filename(path_expression_ptr filename);



  virtual void symbol_dispatch (
				feature_style_processor_base *  output,
				Feature const& f, 
				proj_transform const& prj_trans) const =0;

protected:
    symbolizer_with_image(path_expression_ptr filename);
    symbolizer_with_image(symbolizer_with_image const& rhs);
    path_expression_ptr image_filename_;	
};
}

#endif //MAPNIK_SYMBOLIZER_HPP
