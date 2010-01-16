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

//$Id: plugin.hpp 39 2005-04-10 20:39:53Z pavlenko $

#ifndef PLUGIN_HPP
#define PLUGIN_HPP
// // boost
//#include <boost/utility.hpp>
// // stl
// #include <string>
// // ltdl
//#include <ltdl.h>
#include "boostinc.hpp"

namespace mapnik
{
  class PlugIn; // defined in datasource... an interface to access the plugin datasources without dl
   class PluginInfo : boost::noncopyable
   {         
    private:
         std::string name_;
     //         lt_dlhandle module_;     
    public:
     PluginInfo (const std::string& name,PlugIn* module);
     ~PluginInfo();
     const std::string& name() const;
     PlugIn* handle() const;
   };
}

#endif //PLUGIN_HPP
