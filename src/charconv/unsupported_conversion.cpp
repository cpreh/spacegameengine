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


#include <sge/charconv/exception.hpp>
#include <sge/charconv/unsupported_conversion.hpp>
#include <fcppt/text.hpp>


sge::charconv::unsupported_conversion::unsupported_conversion(
	fcppt::string const &_source,
	fcppt::string const &_dest
)
:
	sge::charconv::exception(
		FCPPT_TEXT("Invalid conversion from ")
		+ _source
		+ FCPPT_TEXT(" to ")
		+ _dest
	)
{
}

sge::charconv::unsupported_conversion::~unsupported_conversion() throw()
{
}

fcppt::string const &
sge::charconv::unsupported_conversion::source() const
{
	return source_;
}

fcppt::string const &
sge::charconv::unsupported_conversion::dest() const
{
	return dest_;
}
