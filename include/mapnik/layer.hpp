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
//$Id: layer.hpp 39 2005-04-10 20:39:53Z pavlenko $


#ifndef INC_LAYER_HPP
#define INC_LAYER_HPP 

#include <mapnik/feature.hpp>
#include <mapnik/datasource.hpp>
// boost
#include <boost/shared_ptr.hpp>
// stl
#include <vector>

//#include "stdinc.hpp"   

namespace mapnik
{
    /*!
     * @brief A Mapnik map layer.
     *
     * Create a layer with a named string and, optionally, an srs string either 
     * with a Proj.4 epsg code ('+init=epsg:<code>') or with a Proj.4 literal 
     * ('+proj=<literal>'). If no srs is specified it will default to 
     * '+proj=latlong +datum=WGS84'
     */
    class layer
    {
    public:
        explicit layer(std::string const& name, std::string const& srs="+proj=latlong +datum=WGS84");
        layer(layer const& l);
        layer& operator=(layer const& l);
        bool operator==(layer const& other) const;
        
        /*!
         * @brief Set the name of the layer.
         */
        void set_name(std::string const& name);
        
        /*!
         * @return the name of the layer.
         */
        const std::string& name() const;
        
        /*!
         * @brief Set the title of the layer.
         */
        void set_title(std::string const& title);
        
        /*!
         * @return the title of the layer.
         */
        const std::string& title() const;
        
        /*!
         * @brief Set the abstract of the layer.
         */
        void set_abstract(std::string const& abstract);
        
        /*!
         * @return the abstract of the layer.
         */
        const std::string& abstract() const;
        
        /*!
         * @brief Set the SRS of the layer.
         */
        void set_srs(std::string const& srs);
        
        /*!
         * @return the SRS of the layer.
         */
        std::string const& srs() const;
        
        /*!
         * @brief Add a new style to this layer.
         *
         * @param stylename The name of the style to add.
         */
        void add_style(std::string const& stylename);
        
        /*!
         * @return the styles list attached to this layer.
         */
        std::vector<std::string> const& styles() const;
        
        /*!
         * @return the styles list attached to this layer
         *         (const version).
         */
        std::vector<std::string>& styles();
        
        /*!
         * @param maxZoom The minimum zoom level to set
         */
        void setMinZoom(double minZoom);
        
        /*!
         * @param maxZoom The maximum zoom level to set
         */
        void setMaxZoom(double maxZoom);
        
        /*!
         * @return the minimum zoom level of the layer.
         */
        double getMinZoom() const;
        
        /*!
         * @return the maximum zoom level of the layer.
         */
        double getMaxZoom() const;
        
        /*!
         * @brief Set whether this layer is active and will be rendered.
         */
        void setActive(bool active);
        
       /*!
         * @return whether this layer is active and will be rendered.
         */
        bool isActive() const;
        
        /*!
         * @brief Set whether this layer is queryable.
         */
        void setQueryable(bool queryable);
        
        /*!
         * @return whether this layer is queryable or not.
         */
        bool isQueryable() const;
        
        /*!
         * @brief Get the visability for a specific scale.
         *
         * @param scale Accepts an integer or float input.
         *
         * @return true if this layer's data is active and visible at a given scale.
         *         Otherwise returns False.
         * @return false if:
         *         scale >= minzoom - 1e-6
         *         or
         *         scale < maxzoom + 1e-6
         */
        bool isVisible(double scale) const;
        
        /*!
         * @param clear_cache Set whether this layer's labels are cached.
         */
        void set_clear_label_cache(bool clear_cache);
        
        /*!
         * @return whether this layer's labels are cached.
         */
        bool clear_label_cache() const; 
        
        /*!
         * @brief Attach a datasource for this layer.
         *
         * @param ds The datasource to attach.
         */
      void set_datasource(PlugIn::datasource_ptr const& ds);
        
        /*!
         * @return the datasource attached to this layer.
         */
      PlugIn::datasource_ptr datasource() const;
        
        /*!
         * @return the geographic envelope/bounding box of the data in the layer.
         */
        box2d<double> envelope() const;
        
        ~layer();
    private:
        void swap(const layer& other);

        std::string name_;
        std::string title_;
        std::string abstract_;
        std::string srs_;
        
        double minZoom_;
        double maxZoom_;
        bool active_;
        bool queryable_;
        bool clear_label_cache_;
        std::vector<std::string>  styles_;
      PlugIn::datasource_ptr ds_;
    };
}

#endif //LAYER_HPP
