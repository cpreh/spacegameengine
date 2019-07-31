//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONVERT_FROM_ENUM_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_FROM_ENUM_HPP_INCLUDED

#include <sge/parse/json/int_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace convert
{

template<
	typename Enum
>
sge::parse::json::int_type
from_enum(
	Enum const _enum
)
{
	static_assert(
		std::is_enum<
			Enum
		>::value,
		"Enum must be an enum type"
	);

	return
		static_cast<
			sge::parse::json::int_type
		>(
			_enum
		);
}

}
}
}
}

#endif
