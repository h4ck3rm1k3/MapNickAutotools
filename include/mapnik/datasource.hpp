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

//$Id: datasource.hpp 43 2005-04-22 18:52:47Z pavlenko $

#ifndef DATASOURCE_HPP
#define DATASOURCE_HPP
// // mapnik
// #include <mapnik/config.hpp>
// #include <mapnik/ctrans.hpp>

// #include <mapnik/feature.hpp>
// #include <mapnik/query.hpp>

// // boost
// #include <boost/utility.hpp>
// #include <boost/shared_ptr.hpp>
// // stl
// #include <map>
// #include <string>
#include "stdinc_datasource.hpp"
//#include <mapnik/params.hpp>
#include <mapnik/feature_layer_desc.hpp>

namespace mapnik {    

    typedef  boost::shared_ptr<Feature> feature_ptr;
    
    struct  Featureset
    {
        virtual feature_ptr next()=0;
        virtual ~Featureset() {};
    };
    
    typedef  boost::shared_ptr<Featureset> featureset_ptr;
    
    class  datasource_exception : public std::exception
    {
    private:
        std::string message_;
    public:
        datasource_exception(const std::string& message=std::string("no reason"))
            :message_(message) {}

        ~datasource_exception() throw() {}
        virtual const char* what() const throw()
        {
            return message_.c_str();
        }
    };
    

  class  datasource : private boost::noncopyable
    {
    public:        

   typedef boost::variant<int,double,std::string> value_holder;
   typedef std::pair<const std::string, value_holder> parameter;
   typedef std::map<const std::string, value_holder> param_map;
   
   template <typename T>
   struct value_extractor_visitor : public boost::static_visitor<>
   {
         value_extractor_visitor(boost::optional<T> & var)
            :var_(var) {}
         
         void operator () (T val) const
         {
            var_ = val;
         }
         
         template <typename T1>
         void operator () (T1 val) const 
         {
            try 
            {
               var_ = boost::lexical_cast<T>(val);
            }
            catch (boost::bad_lexical_cast & ) {}
         }
         
         boost::optional<T> & var_;
   };
   
  
   class parameters : public param_map
   {
         template <typename T> 
         struct converter
         {
               typedef boost::optional<T> return_type;       
               static return_type extract(parameters const& params,
                                          std::string const& name, 
                                          boost::optional<T> const& default_value)
               {
                  boost::optional<T> result(default_value);
                  parameters::const_iterator itr = params.find(name);
                  if (itr != params.end())
                  {
                     boost::apply_visitor(value_extractor_visitor<T>(result),itr->second);
                  }
                  return result;
               }
         };
         
      public:
         
         parameters() {}
         
         template <typename T>
         boost::optional<T> get(std::string const& key) const
         {
            return converter<T>::extract(*this,key, boost::none);
         }
         
         template <typename T>
         boost::optional<T> get(std::string const& key, T const& default_value) const
         {
            return converter<T>::extract(*this,key,boost::optional<T>(default_value));
         }
   };


        enum datasource_t {
            Vector,
            Raster
        };
        
        datasource (parameters const& params)
            : params_(params) {}

        /*!
         * @brief Get the configuration TParameters of the data source.
         *
         * These vary depending on the type of data source.
         *
         * @return The configuration TParameters of the data source.
         */
        parameters const& params() const
        {
            return params_;
        }
        
        /*!
         * @brief Get the type of the datasource
         * @return The type of the datasource (Vector or Raster)
         */
        virtual int type() const=0;
        
        virtual featureset_ptr features(const query& q) const=0;
        virtual featureset_ptr features_at_point(coord2d const& pt) const=0;
        virtual box2d<double> envelope() const=0;
        virtual layer_descriptor  get_descriptor() const=0;
        virtual ~datasource() {};
    protected:
        parameters params_;
    };
    
  // base class for all plugins
  class PlugIn
  {
  public:
    
    //    typedef std::string datasource_name();
    typedef datasource* create_ds(const datasource::parameters& params);
    typedef void destroy_ds(datasource *ds);
    
    class datasource_deleter
    {
    public:
      void operator() (datasource* ds)
      {
	delete ds;
      }
    };
  
    typedef boost::shared_ptr<datasource> datasource_ptr;

    // callbacks
    virtual std::string datasource_name()				     =0;
    virtual datasource* create(const datasource::parameters &params)  =0;
    virtual void destroy(datasource *ds)				   
    {									
      delete ds;							
    }									
  };
    
#define DATASOURCE_PLUGIN(classname)				       \
  extern "C" MAPNIK_EXP std::string datasource_name()			\
  {									\
    return classname::name();						\
  }									\
  extern "C"  MAPNIK_EXP datasource* create(const datasource::parameters &params) \
  {									\
    return new classname(params);					\
  }									\
  extern "C" MAPNIK_EXP void destroy(datasource *ds)			\
  {									\
    delete ds;								\
  }									\
  
}

#endif //DATASOURCE_HPP
