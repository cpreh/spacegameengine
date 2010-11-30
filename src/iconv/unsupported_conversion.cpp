/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/iconv/unsupported_conversion.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>

sge::iconv::unsupported_conversion::unsupported_conversion(
	iconv::encoding_string const &_source,
	iconv::encoding_string const &_dest
)
:
	sge::iconv::exception(
		FCPPT_TEXT("Invalid conversion from ")
		+ fcppt::from_std_string(
			_source
		)
		+ FCPPT_TEXT(" to ")
		+ fcppt::from_std_string(
			_dest
		)
	)
{
}

SGE_ICONV_SYMBOL
sge::iconv::unsupported_conversion::~unsupported_conversion() throw()
{
}

sge::iconv::encoding_string const &
sge::iconv::unsupported_conversion::source() const
{
	return source_;
}

sge::iconv::encoding_string const &
sge::iconv::unsupported_conversion::dest() const
{
	return dest_;
}
