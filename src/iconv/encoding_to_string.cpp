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


#include <sge/iconv/encoding_to_string.hpp>
#include <sge/iconv/exception.hpp>
#include <fcppt/text.hpp>

sge::iconv::encoding_string const
sge::iconv::encoding_to_string(
	iconv::encoding::type const _encoding
)
{
	switch(
		_encoding
	)
	{
	case iconv::encoding::utf8:
		return "UTF-8";
	case iconv::encoding::utf16:
		return "UTF-16";
	case iconv::encoding::utf32:
		return "UTF-32";
	default:
		throw sge::iconv::exception(
			FCPPT_TEXT("Invalid encoding!")
		);
	}
}
