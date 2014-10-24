/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/src/core/include_windows.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/container/raw_vector.hpp>


sge::charconv::backends::windows::wchar_to_utf8::wchar_to_utf8()
{
}

sge::charconv::backends::windows::wchar_to_utf8::~wchar_to_utf8()
{
}


sge::charconv::conversion_status
sge::charconv::backends::windows::wchar_to_utf8::convert(
	sge::charconv::input_range &_input,
	sge::charconv::output_range &_output
)
{
	if(
		_input.empty())
		return sge::charconv::conversion_status::ok;

	if (_input.size() % static_cast<sge::charconv::output_range::difference_type>(2) != 0)
		return sge::charconv::conversion_status::invalid_input;

	typedef
	fcppt::container::raw_vector<wchar_t>
	temp_input_container;

	temp_input_container temp_input(
		static_cast<temp_input_container::size_type>(
			_input.size() / sizeof(wchar_t)));

	fcppt::algorithm::copy_n(
		_input.begin(),
		_input.size(),
		reinterpret_cast<char *>(
			temp_input.data()));

	int const required_output_size =
		WideCharToMultiByte(
			// Codepage
			CP_UTF8,
			// Flags
			0,
			// Input
			temp_input.data(),
			// Input size
			fcppt::cast::truncation_check<
				int
			>(
				temp_input.size()
			),
			// Output
			0,
			// Output size
			0,
			// default char
			0,
			// used default char
			0);

	if(required_output_size == 0xfffd)
		return sge::charconv::conversion_status::invalid_input;

	if(_output.size() < required_output_size)
		return sge::charconv::conversion_status::output_too_small;

	int const conversion_result =
		WideCharToMultiByte(
			// Codepage
			CP_UTF8,
			// Flags
			0,
			// Input
			temp_input.data(),
			// Input size
			fcppt::cast::truncation_check<
				int
			>(
				temp_input.size()
			),
			// Output
			reinterpret_cast<
				LPSTR
			>(
				&*_output.begin()
			),
			// Output size
			fcppt::cast::truncation_check<
				int
			>(
				_output.size()
			),
			// default char
			0,
			// used default char
			0);

	if(conversion_result)
	{
		_input.advance_begin(
			_input.size()
		);

		_output.advance_begin(
			static_cast<
				sge::charconv::output_range::difference_type
			>(
				conversion_result
			)
		);

		return
			sge::charconv::conversion_status::ok;
	}

	FCPPT_ASSERT_ERROR(
		conversion_result == 0
	);

	DWORD const error(
		::GetLastError()
	);

	switch(
		error
	)
	{
	case ERROR_INSUFFICIENT_BUFFER:
		return sge::charconv::conversion_status::output_too_small;
	case ERROR_NO_UNICODE_TRANSLATION:
		return sge::charconv::conversion_status::invalid_input;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
