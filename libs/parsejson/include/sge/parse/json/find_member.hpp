//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_FIND_MEMBER_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/find_member_return_type.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/optional/map.hpp>


namespace sge
{
namespace parse
{
namespace json
{

/**
\brief Searches for a member with the name @a name

\throws invalid_get if the member has a different type than T
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
	sge::charconv::utf8_string const &_name
)
{
	return
		fcppt::optional::map(
			sge::parse::json::find_member_value(
				_members,
				_name
			),
			[](
				auto const _arg
			)
			{
				return
					fcppt::make_ref(
						sge::parse::json::get_exn<
							T
						>(
							_arg.get()
						)
					);
			}
		);
}

}
}
}

#endif
