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


#include "../program_native.hpp"
#include "../../error.hpp"

template<>
sge::ogl::glsl::traits<true>::handle
sge::ogl::glsl::create_program<true>()
{
	SGE_OPENGL_SENTRY
	return glCreateProgram();
}

template<>
GLenum 
sge::ogl::glsl::vertex_shader_type<true>()
{
	return GL_VERTEX_SHADER;
}

template<>
GLenum 
sge::ogl::glsl::pixel_shader_type<true>()
{
	return GL_FRAGMENT_SHADER;
}

template<>
void sge::ogl::glsl::detach_shader<true>(
	const traits<true>::handle program,
	const traits<true>::handle shader)
{
	SGE_OPENGL_SENTRY
	glDetachShader(program, shader);
}

template<>
void sge::ogl::glsl::delete_program<true>(
	const traits<true>::handle program)
{
	SGE_OPENGL_SENTRY
	glDeleteProgram(program);
}

template<>
void sge::ogl::glsl::attach_shader<true>(
	const traits<true>::handle program,
	const traits<true>::handle shader)
{
	SGE_OPENGL_SENTRY
	glAttachShader(program, shader);
}

template<>
void sge::ogl::glsl::link_program<true>(
	const traits<true>::handle program)
{
	SGE_OPENGL_SENTRY
	glLinkProgram(program);
}

template<>
GLint sge::ogl::glsl::get_program_integer<true>(
	const GLenum what,
	const traits<true>::handle program)
{
	SGE_OPENGL_SENTRY
	GLint result;
	glGetProgramiv(program, what, &result);
	return result;
}

template<>
GLint sge::ogl::glsl::get_link_status<true>(
	const traits<true>::handle program)
{
	return get_program_integer<true>(
		GL_LINK_STATUS,
		program);
}

template<>
void sge::ogl::glsl::use_program<true>(
	const traits<true>::handle program)
{
	SGE_OPENGL_SENTRY
	glUseProgram(program);
}

template<>
void sge::ogl::glsl::get_program_info_log<true>(
	const traits<true>::handle program,
	const GLint maxlen,
	GLint *const len,
	char *const data)
{
	SGE_OPENGL_SENTRY
	glGetProgramInfoLog(
		program,
		maxlen,
		len,
		data);
}
