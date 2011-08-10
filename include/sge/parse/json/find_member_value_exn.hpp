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


#ifndef SGE_PARSE_JSON_FIND_MEMBER_VALUE_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_VALUE_EXN_HPP_INCLUDED

#include <sge/parse/json/detail/find_member_return_type.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/member_not_found.hpp>
#include <sge/parse/json/find_member.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace sge
{
namespace parse
{
namespace json
{

template<
	typename Arg
>
typename boost::mpl::if_<
	boost::is_const<
		Arg
	>,
	json::value const &,
	json::value &
>::type
find_member_value_exn(
	Arg &_members,
	fcppt::string const &_name
)
{
	typedef typename json::detail::find_member_return_type<
		json::value,
		Arg
	>::type return_type;

	return_type const ret(
		sge::parse::json::find_member_value(
			_members,
			_name
		)
	);

	if(
		!ret
	)
		throw sge::parse::json::member_not_found(
			FCPPT_TEXT("Cannot find member \"")
			+ _name
			+ FCPPT_TEXT("\" in a json object's member list!")
		);

	return *ret;
}

}
}
}

#endif
