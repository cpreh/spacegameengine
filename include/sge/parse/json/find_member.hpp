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


#ifndef SGE_PARSE_JSON_FIND_MEMBER_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_HPP_INCLUDED

#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/member_name_equal.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/string.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <algorithm>

namespace sge
{
namespace parse
{
namespace json
{

template<
	typename T
>
T const &
find_member(
	member_vector const &members,
	fcppt::string const &name
)
{
	member_vector::const_iterator const it(
		std::find_if(
			members.begin(),
			members.end(),
			member_name_equal(
				name
			)
		)
	);

	if(it == members.end())
		throw exception(
			FCPPT_TEXT("entry \"")
			+ name
			+ FCPPT_TEXT("\" not found")
		);

	return json::get<
		T
	>(
		it->value_
	);
}

}
}
}

#endif
