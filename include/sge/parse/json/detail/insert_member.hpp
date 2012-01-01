/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_JSON_DETAIL_INSERT_MEMBER_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_INSERT_MEMBER_HPP_INCLUDED

#include <sge/parse/json/array.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/detail/insert_member.hpp>
#include <sge/parse/json/detail/member_wrapper.hpp>
#include <sge/parse/json/detail/value_wrapper.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace detail
{

inline
void
insert_member(
	json::member_map &_members,
	json::detail::member_wrapper const &_syn,
	bool &_failed
)
{
	_failed =
		_members.insert(
			std::make_pair(
				_syn.first,
				_syn.second.get()
			)
		).second;

}

}
}
}
}

#endif
