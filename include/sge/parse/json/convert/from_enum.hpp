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


#ifndef SGE_PARSE_JSON_CONVERT_FROM_ENUM_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_FROM_ENUM_HPP_INCLUDED

#include <sge/parse/json/int_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <fcppt/config/external_end.hpp>

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
	sge::parse::json::int_type
>::type
from_enum(
	Enum const &_enum
)
{
	return
		static_cast<
			sge::parse::json::int_type
		>(
			_enum
		);
}

}
}
}
}

#endif
