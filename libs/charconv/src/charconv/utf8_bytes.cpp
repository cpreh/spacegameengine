/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/charconv/exception.hpp>
#include <sge/charconv/utf8_bytes.hpp>
#include <sge/charconv/utf8_char.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


unsigned
sge::charconv::utf8_bytes(
	sge::charconv::utf8_char const _ch
)
{
	if(
		(_ch & 0x80)
		==
		0
	)
		return
			1u;

	if(
		(_ch & 0xE0)
		==
		0xC0
	)
		return
			2u;

	if(
		(_ch & 0xF0)
		==
		0xE0
	)
		return
			3u;

	if(
		(_ch & 0xF8)
		==
		0xF0
	)
		return
			4u;

	throw
		sge::charconv::exception{
			FCPPT_TEXT("Invalid UTF-8 byte")
		};
}
