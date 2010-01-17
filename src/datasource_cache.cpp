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
//$Id: datasource_cache.cpp 23 2005-03-22 22:16:34Z pavlenko $

// mapnik
#include <mapnik/datasource_cache.hpp>

#include <mapnik/datasource.hpp>

#include <mapnik/config_error.hpp>

// boost
#include <boost/version.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string.hpp>

// ltdl
//#include <ltdl.h>

// stl
#include <algorithm>
#include <stdexcept>

namespace mapnik
{
   using namespace std;
   using namespace boost;
   
   bool is_input_plugin (std::string const& filename)
   {
      return boost::algorithm::ends_with(filename,std::string(".input"));
   }
   

   datasource_cache::datasource_cache()
   {
     //if (lt_dlinit()) throw std::runtime_error("lt_dlinit() failed");
   }

   datasource_cache::~datasource_cache()
   {
     //lt_dlexit();
   }

   std::map<string,boost::shared_ptr<PluginInfo> > datasource_cache::plugins_;
   bool datasource_cache::registered_=false;
    
  PlugIn * datasource_cache::create(const datasource::parameters& params) 
   {
       boost::optional<std::string> type = params.get<std::string>("type");
       if ( ! type)
       {
           throw config_error(string("Could not create datasource. Required ") +
                   "parameter 'type' is missing");
       }

       PlugIn::datasource_ptr ds;
       map<string,boost::shared_ptr<PluginInfo> >::iterator itr=plugins_.find(*type);
       if ( itr == plugins_.end() )
       {
           throw config_error(string("Could not create datasource. No plugin ") +
                   "found for type '" + * type + "'");
       }
       if ( ! itr->second->handle())
       {
           throw std::runtime_error(string("Cannot load library: ") + 
				    "lt_dlerror()");
       }

       PlugIn * plugin = itr->second->handle();
	 //lt_dlsym(itr->second->handle(), "create");

       if ( ! plugin)
       {
           throw std::runtime_error(string("Cannot load symbols: ") + 
				    "lt_dlerror()");
       }
#ifdef MAPNIK_DEBUG
       std::clog << "size = " << params.size() << "\n";
       datasource::parameters::const_iterator i = params.begin();
       for (;i!=params.end();++i)
       {
          std::clog << i->first << "=" << i->second << "\n";  
       }
#endif
       //       ds=PlugIn::datasource_ptr(plugincreate_datasource(params), datasource_deleter());

#ifdef MAPNIK_DEBUG
       std::clog<<"datasource="<<ds<<" type="<<type<<std::endl;
#endif
       return plugin;
   }

   bool datasource_cache::insert(const std::string& type, PlugIn * module)
   {
      return plugins_.insert(make_pair(type,boost::shared_ptr<PluginInfo>
                                       (new PluginInfo(type,module)))).second;     
   }

   std::vector<std::string> datasource_cache::plugin_names ()
   {
      std::vector<std::string> names;
      std::map<std::string,boost::shared_ptr<PluginInfo> >::const_iterator itr;
      for (itr = plugins_.begin();itr!=plugins_.end();++itr)
      {
         names.push_back(itr->first);
      }
      return names;
   }
   
   void datasource_cache::register_datasources(const std::string& str)
   {	
#ifdef MAPNIK_THREADSAFE
      mutex::scoped_lock lock(mapnik::singleton<mapnik::datasource_cache, 
                              mapnik::CreateStatic>::mutex_);
#endif
      filesystem::path path(str);
      filesystem::directory_iterator end_itr;
 

      if (exists(path) && is_directory(path))
      {
         for (filesystem::directory_iterator itr(path);itr!=end_itr;++itr )
         {

#if BOOST_VERSION < 103400 
	   if (!is_directory( *itr )  && is_input_plugin(itr->leaf()))      
#else
	     if (!is_directory( *itr )  && is_input_plugin(itr->path().leaf()))   
#endif

            {
               try 
		 {
		   // lt_dlhandle module=lt_dlopen(itr->string().c_str());
// 		   //if (module)
//                   {
// 		    //PlugIn::datasource_name* ds_name = 
// 		      //(PlugIn::datasource_name*) lt_dlsym(module, "datasource_name");
		    
//       //                if (ds_name && insert(ds_name(),module))
// //                      {            
// // #ifdef MAPNIK_DEBUG
// //                         std::clog << "registered datasource : " << ds_name() << std::endl;
// // #endif 
// //                         registered_=true;
// //                      }
//                   }
//                   else
//                   {
//                      std::clog << "Problem loading plugin library: " << itr->string().c_str() << " (libtool error: " << lt_dlerror() << ")" << std::endl;
//                   }
               }
               catch (...) {}
            }
         }   
      }	
   }
}
