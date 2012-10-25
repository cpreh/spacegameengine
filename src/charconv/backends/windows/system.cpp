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


#include <sge/charconv/converter_unique_ptr.hpp>
#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/source_encoding.hpp>
#include <sge/charconv/unsupported_conversion.hpp>
#include <sge/src/charconv/backends/windows/is_utf16.hpp>
#include <sge/src/charconv/backends/windows/system.hpp>
#include <sge/src/charconv/backends/windows/utf16_to_utf32.hpp>
#include <sge/src/charconv/backends/windows/utf32_to_utf16.hpp>
#include <sge/src/charconv/backends/windows/utf8_to_wchar.hpp>
#include <sge/src/charconv/backends/windows/wchar_to_utfwchar8.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::charconv::backends::windows::system::system()
{
}

sge::charconv::backends::windows::system::~system()
{
}

sge::charconv::converter_unique_ptr
sge::charconv::backends::windows::system::create_converter(
	sge::charconv::source_encoding const _source,
	sge::charconv::dest_encoding const _dest
)
{
	if(
		sge::charconv::backends::windows::is_utf16(
			_source.get()
		)
		&&
		_dest.get()
		==
		sge::charconv::encoding::utf32
	)
		return
			sge::charconv::converter_unique_ptr(
				fcppt::make_unique_ptr<
					sge::charconv::backends::windows::utf16_to_utf32
				>()
			);

	if(
		sge::charconv::backends::windows::is_utf16(
			_source.get()
		)
		&&
		_dest.get()
		==
		sge::charconv::encoding::utf8
	)
		return
			sge::charconv::converter_unique_ptr(
				fcppt::make_unique_ptr<
					sge::charconv::backends::windows::wchar_to_utf8
				>()
			);

	if(
		sge::charconv::backends::windows::is_utf16(
			_dest.get()
		)
		&&
		_source.get()
		==
		sge::charconv::encoding::utf32
	)
		return
			sge::charconv::converter_unique_ptr(
				fcppt::make_unique_ptr<
					sge::charconv::backends::windows::utf32_to_utf16
				>()
			);

	if(
		_source.get()
		==
		sge::charconv::encoding::utf8
		&&
		sge::charconv::backends::windows::is_utf16(
			_dest.get()
		)
	)
		return
			sge::charconv::converter_unique_ptr(
				fcppt::make_unique_ptr<
					sge::charconv::backends::windows::utf8_to_wchar
				>()
			);

	throw
		sge::charconv::unsupported_conversion(
			_source,
			_dest
		);
}
