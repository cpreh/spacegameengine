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


#ifndef SGE_PARSE_JSON_FIND_MEMBER_VALUE_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_VALUE_HPP_INCLUDED

#include <sge/parse/json/find_member_return_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename Arg
>
sge::parse::json::find_member_return_type<
	sge::parse::json::value,
	Arg
>
find_member_value(
	Arg &_members,
	fcppt::string const &_name
)
{
	static_assert(
		std::is_same_v<
			std::remove_const_t<
				Arg
			>,
			sge::parse::json::member_map
		>
	);

	return
		fcppt::optional::map(
			fcppt::container::find_opt_mapped(
				_members,
				_name
			),
			[](
				auto const _ref
			)
			{
				return
					fcppt::make_ref(
						_ref.get().get()
					);
			}
		);
}

}
}
}

#endif
