//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_FIND_MEMBER_VALUE_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_MEMBER_VALUE_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/find_member_return_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/make_ref.hpp>
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
	sge::charconv::utf8_string const &_name
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
