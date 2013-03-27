/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/src/charconv/backends/iconv/converter.hpp>
#include <sge/src/charconv/backends/iconv/create_converter.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::charconv::converter_unique_ptr
sge::charconv::backends::iconv::create_converter(
	sge::charconv::source_encoding const _source,
	sge::charconv::dest_encoding const _dest
)
{
	return
		fcppt::make_unique_ptr<
			sge::charconv::backends::iconv::converter
		>(
			_source,
			_dest
		);
}
