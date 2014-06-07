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


#include <sge/charconv/backend.hpp>
#include <sge/charconv/converter.hpp>
#include <sge/charconv/converter_unique_ptr.hpp>
#include <sge/charconv/create_converter.hpp>
#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/source_encoding.hpp>
#if defined(SGE_CHARCONV_ICONV_BACKEND)
#include <sge/src/charconv/backends/iconv/create_converter.hpp>
#elif defined(SGE_CHARCONV_WINDOWS_BACKEND)
#include <sge/src/charconv/backends/windows/create_converter.hpp>
#else
#error "No backend for charconv selected!"
#endif

sge::charconv::converter_unique_ptr
sge::charconv::create_converter(
	sge::charconv::source_encoding const _source_encoding,
	sge::charconv::dest_encoding const _dest_encoding
)
{
	return
#if defined(SGE_CHARCONV_ICONV_BACKEND)
		sge::charconv::backends::iconv::create_converter(
#elif defined(SGE_CHARCONV_WINDOWS_BACKEND)
		sge::charconv::backends::windows::create_converter(
#else
#error "No backend for charconv selected!"
#endif
			_source_encoding,
			_dest_encoding
		);
}
