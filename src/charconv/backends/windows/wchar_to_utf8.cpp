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


#include <sge/charconv/conversion_status.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/output_range.hpp>
#include <sge/charconv/raw_value.hpp>
#include <sge/src/charconv/backends/windows/wchar_to_utf8.hpp>
#include <sge/src/include_windows.hpp>


sge::charconv::backends::windows::wchar_to_utf8::wchar_to_utf8()
{
}

sge::charconv::backends::windows::wchar_to_utf8::~wchar_to_utf8()
{
}

sge::charconv::conversion_status::type
sge::charconv::backends::windows::wchar_to_utf8::convert(
	sge::charconv::input_range &_input,
	sge::charconv::output_range &_output
)
{
	if (_input.size() % static_cast<charconv::output_range::difference_type>(2) != 0)
		return sge::charconv::conversion_status::invalid_input;

	int const required_output_size =
		WideCharToMultiByte(
			// Codepage
			CP_UTF8,
			// Flags
			0,
			// Input
			&(*_input),
			// Input size
			static_cast<int>(
				_input.size()),
			// Output
			&(*_output),
			// Output size
			0,
			// default char
			0
			// used default char
			0);

	if(required_output_size == 0xfffd)
		return sge::charconv::conversion_status::invalid_input;

	// Let the system resize the output until we've got double the input size
	if(_output.size() < required_output_size)
		return sge::charconv::conversion_status::output_too_small;

	int const required_output_size =
		WideCharToMultiByte(
			// Codepage
			CP_UTF8,
			// Flags
			0,
			// Input
			&(*_input),
			// Input size
			static_cast<int>(
				_input.size()),
			// Output
			&(*_output),
			// Output size
			static_cast<int>(
				_output.size()),
			// default char
			0
			// used default char
			0);

	return
		required_output_size
		?
			sge::charconv::conversion_status::ok
		:
			sge::charconv::conversion_status::invalid_input;
}
