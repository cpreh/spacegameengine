//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONVERT_CHOOSE_FUNDAMENTAL_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_CHOOSE_FUNDAMENTAL_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::parse::json::convert
{

template<
	typename Type,
	typename Enable = void
>
struct choose_fundamental;

template<
	typename Type
>
struct choose_fundamental<
	Type,
	std::enable_if_t<
		std::is_integral_v<
			Type
		>
	>
>
{
	using
	type
	=
	sge::parse::json::int_type;
};

template<
	typename Type
>
struct choose_fundamental<
	Type,
	std::enable_if_t<
		std::is_floating_point_v<
			Type
		>
	>
>
{
	using
	type
	=
	sge::parse::json::float_type;
};

template<
	typename Type
>
struct choose_fundamental<
	Type,
	std::enable_if_t<
		std::is_same_v<
			Type,
			sge::charconv::utf8_string
		>
	>
>
{
	using
	type
	=
	sge::charconv::utf8_string;
};

}

#endif
