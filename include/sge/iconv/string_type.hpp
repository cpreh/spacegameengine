/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_ICONV_STRING_TYPE_HPP_INCLUDED
#define SGE_ICONV_STRING_TYPE_HPP_INCLUDED

#include <sge/iconv/encoding.hpp>
#include <boost/cstdint.hpp>
#include <string>

namespace sge
{
namespace iconv
{

template<
	iconv::encoding::type
>
struct string_type;

template<>
struct string_type<
	iconv::encoding::utf8
>
{
	typedef std::basic_string<
		boost::uint8_t
	> type;
};

template<>
struct string_type<
	iconv::encoding::utf16
>
{
	typedef std::basic_string<
		boost::uint16_t
	> type;
};

template<>
struct string_type<
	iconv::encoding::utf32
>
{
	typedef std::basic_string<
		boost::uint32_t
	> type;
};

template<>
struct string_type<
	iconv::encoding::wchar
>
{
	typedef std::wstring type;
};

}
}

#endif
