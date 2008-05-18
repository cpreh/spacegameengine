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


#include "../shader.hpp"
#include <sge/exception.hpp>

template<bool Native>
sge::ogl::glsl::shader<Native>::shader(
	const GLenum type,
	const std::string& source)
: id_(glCreateShader(type))
{
	const char* const ptr = source.c_str();
	const GLint len = static_cast<GLint>(source.size());
	glShaderSource(id(), 1, const_cast<const char**>(&ptr), &len);

	glCompileShader(id());
	
	GLint compile_status;
	glGetShaderiv(id(), GL_COMPILE_STATUS, &compile_status);
	if(compile_status == GL_FALSE)
		throw exception(SGE_TEXT("Compiling a shader failed!"));
	// TODO: better error handling here!
}

template<bool Native>
sge::ogl::glsl::shader<Native>::~shader()
{
	glDeleteShader(id());
}

template<bool Native>
typename sge::ogl::glsl::traits<Native>::handle
sge::ogl::glsl::shader<Native>::id() const
{
	return id_;
}

template class sge::ogl::glsl::shader<true>;
template class sge::ogl::glsl::shader<false>;
