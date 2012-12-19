/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CHARCONV_STRING_TYPE_HPP_INCLUDED
#define SGE_CHARCONV_STRING_TYPE_HPP_INCLUDED

#include <sge/charconv/char_type.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/traits_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace charconv
{

template<
	sge::charconv::encoding Encoding
>
struct string_type
{
private:
	typedef typename sge::charconv::char_type<
		Encoding
	>::type char_type;
public:
	typedef std::basic_string<
		char_type,
		sge::charconv::traits_type<
			char_type
		>
	> type;
};

template<>
struct string_type<
	sge::charconv::encoding::wchar
>
{
	typedef std::wstring type;
};

}
}

#endif
