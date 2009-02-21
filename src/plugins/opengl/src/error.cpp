/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../error.hpp"
#include "../common.hpp"
#include <sge/format.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <exception>

sge::ogl::sentry::sentry(
	std::string const &file_name,
	int const line,
	string const &description)
:
	file_name(file_name),
	line(line),
	description(description)
{}

sge::ogl::sentry::~sentry()
{
	if(std::uncaught_exception())
		return;

	GLenum const error = glGetError();
	if(error != GL_NO_ERROR)
		throw exception(
			((format(
				SGE_TEXT("opengl failed in file \"%1%\", line %2%. The error code was %3%. Description: \"%4%\""))
				% iconv(file_name)
				% line
				% error
				% description)
				.str()));
}
