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


#include <iostream>
#include <ostream>
#include <exception>
#include <boost/format.hpp>
#include "../../../exception.hpp"
#include "../../../iconv.hpp"
#include "../error.hpp"
#include "../common.hpp"

bool sge::ogl::is_error()
{
	const GLenum error = glGetError();
	if(error!=GL_NO_ERROR)
		std::cerr << "OpenGL errorcode: " << error << '\n';
	return error != GL_NO_ERROR;
}

sge::ogl::sentry::sentry(const std::string& function_name,
                         const std::string& file_name,
                         const int line)
: function_name(function_name),
  file_name(file_name),
  line(line)
{}

sge::ogl::sentry::~sentry()
{
	if(std::uncaught_exception())
		return;

	const GLenum error = glGetError();
	if(error != GL_NO_ERROR)
		throw exception(iconv((boost::format("opengl failed in the following function \"%1%\" in file \"%2%\", line %3%. The error code was %4%.")
		                               % function_name % file_name % line % error).str()));
					       // FIXME
}
