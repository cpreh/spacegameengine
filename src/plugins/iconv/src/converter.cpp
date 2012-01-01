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


#include <sge/iconv/converter.hpp>
#include <sge/charconv/const_raw_pointer.hpp>
#include <sge/charconv/exception.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/output_range.hpp>
#include <sge/charconv/raw_pointer.hpp>
#include <sge/charconv/unsupported_conversion.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cerrno>
#include <cstddef>
#include <iconv.h>
#include <fcppt/config/external_end.hpp>


sge::iconv::converter::converter(
	sge::iconv::encoding_string const &_source,
	sge::iconv::encoding_string const &_dest
)
:
	iconv_(
		::iconv_open(
			_dest.c_str(),
			_source.c_str()
		)
	)
{
	if(
		iconv_
		== reinterpret_cast<
			::iconv_t
		>(
			-1
		)
	)
		throw sge::charconv::unsupported_conversion(
			fcppt::from_std_string(
				_source
			),
			fcppt::from_std_string(
				_dest
			)
		);
}

sge::iconv::converter::~converter()
{
	::iconv_close(
		iconv_
	);
}

sge::charconv::conversion_status::type
sge::iconv::converter::convert(
	charconv::input_range &_input,
	charconv::output_range &_output
)
{
	char *source(
		const_cast<
			char *
		>(
			reinterpret_cast<
				char const *
			>(
				_input.begin()
			)
		)
	);

	std::size_t in_bytes_left(
		static_cast<
			std::size_t
		>(
			_input.size()
		)
	);

	char *dest(
		reinterpret_cast<
			char *
		>(
			_output.begin()
		)
	);

	std::size_t out_bytes_left(
		static_cast<
			std::size_t
		>(
			_output.size()
		)
	);

	::size_t const ret(
		::iconv(
			iconv_,
			&source,
			&in_bytes_left,
			&dest,
			&out_bytes_left
		)
	);

	_input =
		charconv::input_range(
			// TODO: a constructor with (ptr, size) would save some typing
			reinterpret_cast<
				charconv::const_raw_pointer
			>(
				source
			),
			reinterpret_cast<
				charconv::const_raw_pointer
			>(
				source
			)
			+ in_bytes_left
		);

	_output =
		charconv::output_range(
			reinterpret_cast<
				charconv::raw_pointer
			>(
				dest
			),
			reinterpret_cast<
				charconv::raw_pointer
			>(
				dest
			)
			+ out_bytes_left
		);

	if(
		ret
		!= static_cast<
			std::size_t
		>(
			-1
		)
	)
		return charconv::conversion_status::ok;

	switch(
		errno
	)
	{
	case E2BIG:
		return charconv::conversion_status::output_too_small;
	case EILSEQ:
		return charconv::conversion_status::invalid_input;
	case EINVAL:
		return charconv::conversion_status::incomplete_input;
	default:
		throw sge::charconv::exception(
			FCPPT_TEXT(
				"Invalid errno on iconv error!"
			)
		);
	}
}
