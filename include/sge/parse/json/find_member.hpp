/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/parse/json/detail/find_member_return_type.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/member_name_equal.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <algorithm>

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
typename detail::find_member_return_type<
	T,
	Arg
>::type
find_member(
	Arg &_members,
	fcppt::string const &_name
)
{
	typedef typename boost::mpl::if_<
		boost::is_const<
			Arg
		>,
		member_vector::const_iterator,
		member_vector::iterator
	>::type iterator;

	iterator const it(
		std::find_if(
			_members.begin(),
			_members.end(),
			json::member_name_equal(
				_name
			)
		)
	);

	return 
		it == _members.end()
		?
			0
		:
			&json::get<
				T
			>(
				it->value_
			);
}

}
}
}

#endif
