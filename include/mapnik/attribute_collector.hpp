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

#ifndef ATTRIBUTE_COLLECTOR_HPP
#define ATTRIBUTE_COLLECTOR_HPP

// mapnik
#include <mapnik/feature_layer_desc.hpp>
#include <mapnik/rule.hpp>
#include <mapnik/path_expression_grammar.hpp>

// boost
#include <boost/utility.hpp>
#include <boost/variant.hpp>
#include <boost/concept_check.hpp>
// stl
#include "stdinc.hpp"


namespace mapnik {

 typedef const std::basic_string<char, std::char_traits<char>, std::allocator<char> >& TARG;

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }


  /* duplicate
  bool operator ()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> >&, const std::basic_string<char, std::char_traits<char>, std::allocator<char> >&) const
  {
    return s1 < s2;
  }
  bool operator()(TARG s1, TARG s2) const
  {
    return s1 < s2;
  }

  */


  bool operator()(const std::string & s1, const std::string & s2) const
  {
    return s1 < s2;
  }
};
typedef std::set<std::string, ltstr> TNameSet;
typedef TNameSet& TNameSetRef;


struct expression_attributes : boost::static_visitor<void>
{



    explicit expression_attributes(TNameSet & names)
	: names_(names) {}
    
    void operator() (value_type const& x) const 
    {
	boost::ignore_unused_variable_warning(x);
    }
    
    void operator() (attribute const& attr) const
    {
	names_.insert(attr.name());
    }
    
    template <typename Tag> 
    void operator() (binary_node<Tag> const& x) const
    {
        boost::apply_visitor(expression_attributes(names_),x.left);
        boost::apply_visitor(expression_attributes(names_),x.right);
        
    }

    template <typename Tag>
    void operator() (unary_node<Tag> const& x) const
    {
	boost::apply_visitor(expression_attributes(names_),x.expr);	
    }
    
    void operator() (regex_match_node const& x) const
    {
	boost::apply_visitor(expression_attributes(names_),x.expr);
    }
    
    void operator() (regex_replace_node const& x) const
    {
	boost::apply_visitor(expression_attributes(names_),x.expr);
    }
    
private:
    mutable TNameSetRef names_;
};

struct symbolizer_attributes : public boost::static_visitor<>
{
    symbolizer_attributes(TNameSetRef names)
	: names_(names) {}
	
    template <typename T>
    void operator () (T const&) const {}
    
    void operator () (text_symbolizer const& sym)
    {
	expression_ptr const& name_expr = sym.get_name();
	if (name_expr)
	{
	    expression_attributes f_attr(names_);
	    boost::apply_visitor(f_attr,*name_expr);
	}
    }
    
    void operator () (point_symbolizer const& sym)
    {	
	path_expression_ptr const& filename_expr = sym.get_filename();
	if (filename_expr)
	{
	    path_processor_type::collect_attributes(*filename_expr,names_);
	}
    }

    void operator () (line_pattern_symbolizer const& sym)
    {	
	path_expression_ptr const& filename_expr = sym.get_filename();
	if (filename_expr)
	{
	    path_processor_type::collect_attributes(*filename_expr,names_);
	}
    }

    void operator () (polygon_pattern_symbolizer const& sym)
    {	
	path_expression_ptr const& filename_expr = sym.get_filename();
	if (filename_expr)
	{
	    path_processor_type::collect_attributes(*filename_expr,names_);
	}
    }
    
    void operator () (shield_symbolizer const& sym)
    {
	expression_ptr const& name_expr = sym.get_name();
	if (name_expr)
	{
	    expression_attributes name_attr(names_);
	    boost::apply_visitor(name_attr,*name_expr);
	}
	
	path_expression_ptr const& filename_expr = sym.get_filename();
	if (filename_expr)
	{
	    path_processor_type::collect_attributes(*filename_expr,names_);
	}
    }

    // TODO - support remaining syms
    
private:
    TNameSetRef names_;
};


class attribute_collector : public boost::noncopyable
{
private:
    TNameSetRef names_;
public:
    
    attribute_collector(TNameSetRef names)
	: names_(names) {}
	
    template <typename RuleType>
    void operator() (RuleType const& r)
    {
	typename RuleType::symbolizers const& symbols = r.get_symbolizers();
	typename RuleType::symbolizers::const_iterator symIter=symbols.begin();
	symbolizer_attributes s_attr(names_);
	while (symIter != symbols.end())
	{
	    boost::apply_visitor(s_attr,*symIter++);
	}
	    
	expression_ptr const& expr = r.get_filter();
	expression_attributes f_attr(names_);
	boost::apply_visitor(f_attr,*expr);
    } 	
};   

} // namespace mapnik

#endif //ATTRIBUTE_COLLECTOR_HPP
