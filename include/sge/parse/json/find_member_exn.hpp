/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_JSON_FIND_MEMBER_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_EXN_HPP_INCLUDED

#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/member_not_found.hpp>
#include <sge/parse/json/find_member.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

namespace sge
{
namespace parse
{
namespace json
{

/// Searches for a member with the name @a name
/**
 * @throws member_not_found if the member is not found
 * @throws invalid_get if the member has a different type than T
*/
template<
	typename T
>
T const &
find_member_exn(
	member_vector const &members,
	fcppt::string const &name
)
{
	T const *const ret(
		sge::parse::json::find_member<
			T
		>(
			members,
			name
		)
	);

	if(
		!ret
	)
		throw sge::parse::json::member_not_found(
			FCPPT_TEXT("")
		);
	
	return *ret;
}

}
}
}

#endif
