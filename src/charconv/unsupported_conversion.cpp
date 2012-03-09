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


#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/encoding_to_string.hpp>
#include <sge/charconv/exception.hpp>
#include <sge/charconv/source_encoding.hpp>
#include <sge/charconv/unsupported_conversion.hpp>
#include <fcppt/text.hpp>


sge::charconv::unsupported_conversion::unsupported_conversion(
	sge::charconv::source_encoding const _source,
	sge::charconv::dest_encoding const _dest
)
:
	sge::charconv::exception(
		FCPPT_TEXT("Invalid conversion from ")
		+
		sge::charconv::encoding_to_string(
			_source.get()
		)
		+ FCPPT_TEXT(" to ")
		+
		sge::charconv::encoding_to_string(
			_dest.get()
		)
	),
	source_(
		_source
	),
	dest_(
		_dest
	)
{
}

sge::charconv::unsupported_conversion::~unsupported_conversion() throw()
{
}

sge::charconv::source_encoding const
sge::charconv::unsupported_conversion::source() const
{
	return source_;
}

sge::charconv::dest_encoding const
sge::charconv::unsupported_conversion::dest() const
{
	return dest_;
}
