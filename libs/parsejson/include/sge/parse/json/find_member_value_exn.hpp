//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_FIND_MEMBER_VALUE_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_VALUE_EXN_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/member_not_found.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>
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
std::conditional_t<
	std::is_const_v<
		Arg
	>,
	sge::parse::json::value const &,
	sge::parse::json::value &
>
find_member_value_exn(
	Arg &_members,
	sge::charconv::utf8_string const &_name
)
{
	return
		fcppt::optional::to_exception(
			sge::parse::json::find_member_value(
				_members,
				_name
			),
			[
				&_name
			]{
				return
					sge::parse::json::member_not_found(
						FCPPT_TEXT("Cannot find member \"")
						+
						sge::parse::json::detail::to_fcppt_string(
							_name
						)
						+
						FCPPT_TEXT("\" in a json object's member list!")
					);
			}
		).get();
}

}
}
}

#endif
