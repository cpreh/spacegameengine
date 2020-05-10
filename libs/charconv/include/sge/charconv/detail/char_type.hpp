//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_DETAIL_CHAR_TYPE_HPP_INCLUDED
#define SGE_CHARCONV_DETAIL_CHAR_TYPE_HPP_INCLUDED

#include <sge/charconv/encoding.hpp>


namespace sge
{
namespace charconv
{
namespace detail
{

template<
	sge::charconv::encoding
>
struct char_type;

template<>
struct char_type<
	sge::charconv::encoding::utf8
>
{
	using
	type
	=
	char;
};

template<>
struct char_type<
	sge::charconv::encoding::utf16
>
{
	using
	type
	=
	char16_t;
};

template<>
struct char_type<
	sge::charconv::encoding::utf32
>
{
	using
	type
	=
	char32_t;
};

template<>
struct char_type<
	sge::charconv::encoding::wchar
>
{
	using
	type
	=
	wchar_t;
};

}
}
}

#endif
