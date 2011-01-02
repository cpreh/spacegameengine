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


#include "../encoding_to_string.hpp"
#include <fcppt/endianness/is_little_endian.hpp>
#include <fcppt/text.hpp>

sge::iconv::encoding_string const
sge::iconv::encoding_to_string(
	charconv::encoding::type const _encoding
)
{
	switch(
		_encoding
	)
	{
	case charconv::encoding::utf8:
		return "UTF-8";
	case charconv::encoding::utf16:
		return 
			fcppt::endianness::is_little_endian()
			?
				"UTF-16LE"
			:
				"UTF-16BE";
	case charconv::encoding::utf32:
		return
			fcppt::endianness::is_little_endian()
			?
				"UTF-32LE"
			:
				"UTF-32BE";
	case charconv::encoding::wchar:
		return "WCHAR_T";
	}

	throw sge::charconv::exception(
		FCPPT_TEXT("Invalid encoding!")
	);
}
