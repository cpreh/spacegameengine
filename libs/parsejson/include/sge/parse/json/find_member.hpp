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
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/map.hpp>


namespace sge::parse::json
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
	fcppt::reference<
		Arg
	> const _members,
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
				auto const _arg_ref
			)
			{
				return
					sge::parse::json::get_exn<
						T
					>(
						_arg_ref
					);
			}
		);
}

}

#endif
