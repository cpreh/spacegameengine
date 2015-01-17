/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/charconv/conversion_status.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/output_range.hpp>
#include <sge/charconv/raw_value.hpp>
#include <sge/src/charconv/backends/windows/utf32_to_utf16.hpp>
#include <fcppt/endianness/convert.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fcppt/config/external_end.hpp>


sge::charconv::backends::windows::utf32_to_utf16::utf32_to_utf16()
{
}

sge::charconv::backends::windows::utf32_to_utf16::~utf32_to_utf16()
{
}

sge::charconv::conversion_status
sge::charconv::backends::windows::utf32_to_utf16::convert(
	sge::charconv::input_range &_input,
	sge::charconv::output_range &_output
)
{
	// Let the system resize the output until we've got double the input size
	if(_output.size() < _input.size())
		return sge::charconv::conversion_status::output_too_small;

	if (_input.size() % static_cast<charconv::output_range::difference_type>(4) != 0)
		return sge::charconv::conversion_status::invalid_input;

	while(_input.begin() != _input.end())
	{
		typedef
		std::uint16_t
		utf16;

		typedef
		std::uint32_t
		utf32;

		utf32 const current_codepoint =
			fcppt::endianness::convert(
				static_cast<utf32>(
					static_cast<utf32>(
						(*(_input.begin()+0))) << 0  |
					static_cast<utf32>(
						(*(_input.begin()+1))) << 8  |
					static_cast<utf32>(
						(*(_input.begin()+2))) << 16 |
					static_cast<utf32>(
						(*(_input.begin()+3))) << 24),
				fcppt::endianness::format::little);

		_input.advance_begin(
			4);

		utf16 const
			higher_part =
				static_cast<utf16>(
					current_codepoint >> 16),
			lower_part =
				static_cast<utf16>(
					current_codepoint & 0xffff);

		if(!higher_part)
		{
			std::memcpy(
				&(*_output.begin()),
				&lower_part,
				2u);

			_output.advance_begin(
				2);

			continue;
		}

		utf16 const
			high_converted =
				static_cast<utf16>(
					((current_codepoint - 0x10000) >> 10u) + 0xd800),
			low_converted =
				static_cast<utf16>(
					((current_codepoint - 0x10000) & 0x3ff) + 0xdc00);

		std::memcpy(
			&(*(_output.begin()+0)),
			&high_converted,
			2u);

		std::memcpy(
			&(*(_output.begin()+2)),
			&low_converted,
			2u);

		_output.advance_begin(
			4);
	}

	return sge::charconv::conversion_status::ok;
}
