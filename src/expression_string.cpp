#include <mapnik/stdinc.hpp>
/*****************************************************************************
 * 
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2009 Artem Pavlenko
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

#include <mapnik/expression_string.hpp>
#include <boost/variant.hpp>

namespace mapnik
{

struct expression_string : boost::static_visitor<void>
{
    explicit expression_string(std::string & str)
	: str_(str) {}
    
    void operator() (value_type const& x) const
    { 
	str_ += x.to_expression_string() ; 
    }
    
    void operator() (attribute const& attr) const
    {
        str_ += "[";
	str_ += attr.name();
	str_ += "]";
    }
    
    template <typename Tag> 
    void operator() (binary_node<Tag> const& x) const
    {
        if (x.type() != tags::mult::str() && x.type() != tags::div::str())
        {
            str_ += "(";
        }
        
        boost::apply_visitor(expression_string(str_),x.left);
        str_ += x.type();
        boost::apply_visitor(expression_string(str_),x.right);
        if (x.type() != tags::mult::str() && x.type() != tags::div::str())
        {
            str_ += ")";
        }
    }

    template <typename Tag>
    void operator() (unary_node<Tag> const& x) const
    {
	str_ += Tag::str();
	str_ += "(";
	boost::apply_visitor(expression_string(str_),x.expr);	
	str_ += ")";
    }
    
    void operator() (regex_match_node const & x) const
    {
	boost::apply_visitor(expression_string(str_),x.expr);
	str_ +=".match(";
	std::string utf8;
	//	UnicodeString ustr = UnicodeString::fromUTF32( &x.pattern.str()[0] ,x.pattern.str().length());
	UnicodeString ustr((UChar32) &x.pattern.str()[0] ,x.pattern.str().length());
	to_utf8(ustr,utf8);
	str_ += utf8;
	str_ +=")";
    }
    
    void operator() (regex_replace_node const & x) const
    {
	boost::apply_visitor(expression_string(str_),x.expr);
	str_ +=".replace(";
	std::string utf8;
	//	UnicodeString ustr = UnicodeString::fromUTF32( &x.pattern.str()[0] ,x.pattern.str().length());
	UnicodeString ustr((UChar32) &x.pattern.str()[0] ,x.pattern.str().length());
	to_utf8(ustr,utf8);
	str_ += "'";
	str_ += utf8;
	str_ +="','";
	to_utf8(x.format ,utf8);
	str_ += utf8;
	str_ +="')";
    }

private:
    mutable std::string & str_;
};

std::string to_expression_string(expr_node const& node)
{
    std::string str;
    expression_string functor(str);
    boost::apply_visitor(functor,node);
    return str;
}

}
