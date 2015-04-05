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


#ifndef SGE_PARSE_JSON_FIND_MEMBER_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_HPP_INCLUDED

#include <sge/parse/json/find_member_return_type.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace parse
{
namespace json
{

/// Searches for a member with the name @a name
/**
 * @return 0 if the member was not found
 * @throws invalid_get if the member has a different type than T
*/
template<
	typename T,
	typename Arg
>
sge::parse::json::find_member_return_type<
	T,
	Arg
>
find_member(
	Arg &_members,
	fcppt::string const &_name
)
{
	return
		fcppt::optional_bind_construct(
			sge::parse::json::find_member_value(
				_members,
				_name
			),
			[](
				typename
				sge::parse::json::find_member_return_type<
					T,
					Arg
				>::element_type _arg
			)
			{
				return
					sge::parse::json::get_exn<
						T
					>(
						_arg
					);
			}
		);
}

}
}
}

#endif
