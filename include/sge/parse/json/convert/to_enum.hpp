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


#ifndef SGE_PARSE_JSON_CONVERT_TO_ENUM_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_TO_ENUM_HPP_INCLUDED

#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/text.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_enum.hpp>

namespace sge
{
namespace parse
{
namespace json
{
namespace convert
{

template<
	typename Enum
>
typename boost::enable_if<
	boost::is_enum<
		Enum
	>,
	Enum
>::type
to_enum(
	json::value const &_value,
	Enum const _max_value
)
{
	json::int_type const int_value(
		json::get<
			json::int_type
		>(
			_value
		)
	);

	if(
		int_value < 0
		||
		int_value
		>=
		static_cast<
			json::int_type
		>(
			_max_value
		)
	)
		throw sge::parse::json::exception(
			FCPPT_TEXT("Enum value out of range!")
		);

	return
		static_cast<
			Enum
		>(
			int_value
		);
}

}
}
}
}

#endif
