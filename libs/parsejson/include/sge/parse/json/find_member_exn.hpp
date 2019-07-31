//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_FIND_MEMBER_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_EXN_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


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
	typename T,
	typename Arg
>
std::conditional_t<
	std::is_const_v<
		Arg
	>,
	T const &,
	T &
>
find_member_exn(
	Arg &_members,
	sge::charconv::utf8_string const &_name
)
{
	return
		sge::parse::json::get_exn<
			T
		>(
			sge::parse::json::find_member_value_exn(
				_members,
				_name
			)
		);
}

}
}
}

#endif
