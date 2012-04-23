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


#include <sge/charconv/const_raw_pointer.hpp>
#include <sge/charconv/conversion_status.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/output_range.hpp>
#include <sge/src/charconv/backends/windows/utf8_to_wchar.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/include_windows.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::charconv::backends::windows::utf8_to_wchar::utf8_to_wchar()
{
}

sge::charconv::backends::windows::utf8_to_wchar::~utf8_to_wchar()
{
}

sge::charconv::conversion_status::type
sge::charconv::backends::windows::utf8_to_wchar::convert(
	sge::charconv::input_range &_input,
	sge::charconv::output_range &_output
)
{
	if(
		_input.empty()
	)
		return sge::charconv::conversion_status::ok;

	typedef fcppt::container::raw_vector<
		wchar_t
	> temp_output_container;

	temp_output_container temp_output(
		static_cast<
			temp_output_container::size_type
		>(
			_output.size()
		)
	);

	int const ret(
		::MultiByteToWideChar(
			CP_UTF8,
			MB_ERR_INVALID_CHARS
			|
			MB_PRECOMPOSED,
			reinterpret_cast<
				LPCSTR
			>(
				&*_input.begin()
			),
			fcppt::truncation_check_cast<
				int
			>(
				_input.size()
			),
			temp_output.data(),
			fcppt::truncation_check_cast<
				int
			>(
				temp_output.size()
			)
		)
	);

	if(
		ret > 0
	)
	{
		_input.advance_begin(
			_input.size()
		);

		std::size_t const converted_bytes(
			static_cast<
				std::size_t
			>(
				ret
			)
			* sizeof(wchar_t)
		);

		fcppt::algorithm::copy_n(
			reinterpret_cast<
				sge::charconv::const_raw_pointer
			>(
				temp_output.data()
			),
			converted_bytes,
			&*_output.begin()
		);

		_output.advance_begin(
			static_cast<
				sge::charconv::output_range::size_type
			>(
				converted_bytes
			)
		);

		return sge::charconv::conversion_status::ok;
	}

	FCPPT_ASSERT_ERROR(
		ret == 0
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
