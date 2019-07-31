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
	typedef char type;
};

template<>
struct char_type<
	sge::charconv::encoding::utf16
>
{
	typedef char16_t type;
};

template<>
struct char_type<
	sge::charconv::encoding::utf32
>
{
	typedef char32_t type;
};

template<>
struct char_type<
	sge::charconv::encoding::wchar
>
{
	typedef wchar_t type;
};

}
}
}

#endif
