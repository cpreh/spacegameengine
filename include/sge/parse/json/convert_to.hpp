/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_PARSE_JSON_CONVERT_TO_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_TO_HPP_INCLUDED

#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/float_type.hpp>
#include <fcppt/type_traits/is_iterable.hpp>
#include <fcppt/string.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace parse
{
namespace json
{
template<typename T>
typename
boost::enable_if_c
<
	boost::is_same<T,sge::parse::json::object>::value ||
	boost::is_same<T,sge::parse::json::array>::value ||
	boost::is_same<T,sge::parse::json::null>::value ||
	boost::is_same<T,fcppt::string>::value ||
	boost::is_same<T,bool>::value,
	sge::parse::json::value
>::type
convert_to(
	T const &t)
{
	return
		t;
}

template<typename T>
typename
boost::enable_if_c
<
	boost::is_integral<T>::value &&
	!boost::is_same<T,bool>::value,
	sge::parse::json::value
>::type
convert_to(
	T const &t)
{
	return
		static_cast<sge::parse::json::int_type>(
			t);
}

template<typename T>
typename
boost::enable_if_c
<
	boost::is_floating_point<T>::value,
	sge::parse::json::value
>::type
convert_to(
	T const &t)
{
	return
		static_cast<sge::parse::json::float_type>(
			t);
}

// TODO: We could make a convert_to which converts from a tuple to a
// (heterogenous) array
template<typename T>
typename
boost::enable_if_c
<
	fcppt::type_traits::is_iterable<T>::value &&
	!boost::is_same<T,fcppt::string>::value,
	sge::parse::json::value
>::type
convert_to(
	T const &t)
{
	sge::parse::json::array result;
	for(typename T::const_iterator i = t.begin(); i != t.end(); ++i)
		result.elements.push_back(
			json::convert_to(
				*i));
	return result;
}
}
}
}

#endif
