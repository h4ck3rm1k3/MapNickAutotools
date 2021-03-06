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

#ifndef FONT_SET_HPP
#define FONT_SET_HPP
// mapnik
#include <mapnik/config.hpp>
// boost
#include <boost/shared_ptr.hpp>
// stl
#include <string>
#include <vector>
//#include "stdinc.hpp"   
namespace mapnik
{
    class  font_set
    {
        public:
            font_set(); 
            font_set(std::string const& name); 
            font_set(font_set const& rhs);
            font_set& operator=(font_set const& rhs);
            unsigned size() const;
            std::string const& get_name() const;
            void add_face_name(std::string);
            std::vector<std::string> const& get_face_names() const;
            ~font_set();
        private:
            std::string name_;
            std::vector<std::string> face_names_;
    };
}

#endif //FONT_SET_HPP
