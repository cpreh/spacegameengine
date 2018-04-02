/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/parse/json/detail/is_iterable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

// TODO: Add a test for this. This code is probably broken.
template<
	typename T
>
std::enable_if_t<
	std::is_same<
		T,
		sge::parse::json::object
	>::value
	||
	std::is_same<
		T,
		sge::parse::json::array
	>::value
	||
	std::is_same<
		T,
		sge::parse::json::null
	>::value
	||
	std::is_same<
		T,
		fcppt::string
	>::value
	||
	std::is_same<
		T,
		bool
	>::value,
	sge::parse::json::value
>
convert_to(
	T const &_value
)
{
	return
		sge::parse::json::value(
			_value
		);
}

template<
	typename T
>
std::enable_if_t<
	std::is_integral<
		T
	>::value
	&&
	not
	std::is_same<
		T,
		bool
	>::value,
	sge::parse::json::value
>
convert_to(
	T const &_value
)
{
	return
		sge::parse::json::value(
			static_cast<
				sge::parse::json::int_type
			>(
				_value
			)
		);
}

template<
	typename T
>
std::enable_if_t<
	std::is_floating_point<
		T
	>::value,
	sge::parse::json::value
>
convert_to(
	T const &_value
)
{
	return
		sge::parse::json::value(
			static_cast<
				sge::parse::json::float_type
			>(
				_value
			)
		);
}

// TODO: We could make a convert_to which converts from a tuple to a
// (heterogenous) array
template<
	typename T
>
std::enable_if_t<
	sge::parse::json::detail::is_iterable<
		T
	>::value
	&&
	not
	std::is_same<
		T,
		fcppt::string
	>::value,
	sge::parse::json::value
>
convert_to(
	T const &_value
)
{
	return
		sge::parse::json::value(
			fcppt::algorithm::map<
				sge::parse::json::array
			>(
				_value,
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
