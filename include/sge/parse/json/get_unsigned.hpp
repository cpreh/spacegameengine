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


#ifndef SGE_PARSE_JSON_GET_UNSIGNED_HPP_INCLUDED
#define SGE_PARSE_JSON_GET_UNSIGNED_HPP_INCLUDED

#include <sge/parse/json/get.hpp>
#include <sge/parse/json/invalid_get.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/utility/enable_if.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename T,
	typename Arg
>
typename boost::enable_if<
	boost::is_unsigned<
		T
	>,
	T
>::type
get_unsigned(
	Arg &_val
)
{
	int const result(
		json::get<
			int
		>(
			_val
		)
	);

	if(
		result < 0
	)
		throw json::invalid_get(
			FCPPT_TEXT("json::get_unsigned<")
			+ fcppt::type_name(
				typeid(T)
			)
			+ FCPPT_TEXT("> failed! Value is negative: ")
			+ fcppt::insert_to_fcppt_string(
				result
			)
		);

	return
		static_cast<
			T
		>(
			result
		);
}

}
}
}

#endif
