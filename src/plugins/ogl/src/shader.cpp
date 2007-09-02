/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#if 0
#include "../../../exception.hpp"
#include "../shader.hpp"

sge::ogl::shader::shader(const GLenum type, const std::string& source)
: id_(glCreateShader(type))
{
	const char* const ptr = source.c_str();
	const int len = source.size();
	glShaderSource(id(), 1, const_cast<const char**>(&ptr), &len);

	glCompileShader(id());
	
	int compile_status;
	glGetShaderiv(id(), GL_COMPILE_STATUS, &compile_status);
	if(compile_status == GL_FALSE)
		throw exception("Compiling a shader failed!");
}

sge::ogl::shader::~shader()
{
	glDeleteShader(id());
}

GLuint sge::ogl::shader::id() const
{
	return id_;
}
#endif
