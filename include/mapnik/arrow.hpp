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

#ifndef ARROW_HPP
#define ARROW_HPP

#include <mapnik/box2d.hpp>

namespace mapnik {

   class arrow
   {
      public:
         arrow();
         void rewind(unsigned path_id);
         unsigned vertex(double* x, double* y);
         box2d<double> extent() const;   
      private:
         unsigned pos_;
         double x_[7];
         double y_[7];
         unsigned cmd_[9];
   };   
}

#endif // ARROW_HPP
