/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/parse/json/array.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/type_traits/is_iterable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
template<typename T>
typename
boost::enable_if
<
	boost::mpl::or_
	<
		std::is_same<T,sge::parse::json::object>,
		std::is_same<T,sge::parse::json::array>,
		std::is_same<T,sge::parse::json::null>,
		std::is_same<T,fcppt::string>,
		std::is_same<T,bool>
	>,
	sge::parse::json::value
>::type
convert_to(
	T const &t)
{
	return
		sge::parse::json::value(
			t
		);
}

template<typename T>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		std::is_integral<T>,
		boost::mpl::not_
		<
			std::is_same<T,bool>
		>
	>,
	sge::parse::json::value
>::type
convert_to(
	T const &t)
{
	return
		sge::parse::json::value(
			static_cast<sge::parse::json::int_type>(
				t));
}

template<typename T>
typename
boost::enable_if
<
	std::is_floating_point<T>,
	sge::parse::json::value
>::type
convert_to(
	T const &t)
{
	return
		sge::parse::json::value(
			static_cast<sge::parse::json::float_type>(
				t));
}

// TODO: We could make a convert_to which converts from a tuple to a
// (heterogenous) array
template<typename T>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		fcppt::type_traits::is_iterable<T>,
		boost::mpl::not_
		<
			std::is_same<T,fcppt::string>
		>
	>,
	sge::parse::json::value
>::type
convert_to(
	T const &t)
{
	return
		sge::parse::json::value(
			fcppt::algorithm::map<
				sge::parse::json::array
			>(
				t,
				[](
					typename
					T::value_type const &_arg
				)
				{
					return
						sge::parse::json::convert_to(
							_arg
						);
				}
			)
		);
}

}
}
}

#endif
