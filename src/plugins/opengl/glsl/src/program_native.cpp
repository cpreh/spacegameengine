/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../../sentry.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/text.hpp>

template<>
sge::ogl::glsl::traits<true>::handle
sge::ogl::glsl::create_program<true>()
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glCreateProgram failed"),
		sge::renderer::glsl::exception
	)

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
	traits<true>::handle const program,
	traits<true>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glDetachShader failed"),
		sge::renderer::glsl::exception
	)

	glDetachShader(program, shader);
}

template<>
void sge::ogl::glsl::delete_program<true>(
	traits<true>::handle const program)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glDeleteProgram failed"),
		sge::renderer::glsl::exception
	)

	glDeleteProgram(program);
}

template<>
void sge::ogl::glsl::attach_shader<true>(
	traits<true>::handle const program,
	traits<true>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glAttachShader failed"),
		sge::renderer::glsl::exception
	)

	glAttachShader(program, shader);
}

template<>
void sge::ogl::glsl::link_program<true>(
	traits<true>::handle const program)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glLinKProgram failed"),
		sge::renderer::glsl::exception
	)

	glLinkProgram(program);
}

template<>
GLint sge::ogl::glsl::program_integer<true>(
	GLenum const what,
	traits<true>::handle const program)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetProgramiv failed"),
		sge::renderer::glsl::exception
	)

	GLint result;
	glGetProgramiv(program, what, &result);
	return result;
}

template<>
GLint sge::ogl::glsl::link_status<true>(
	traits<true>::handle const program)
{
	return program_integer<true>(
		GL_LINK_STATUS,
		program
	);
}

template<>
void sge::ogl::glsl::use_program<true>(
	traits<true>::handle const program)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glUseProgram failed"),
		sge::renderer::glsl::exception
	)

	glUseProgram(program);
}

template<>
void sge::ogl::glsl::program_info_log<true>(
	traits<true>::handle const program,
	GLint const maxlen,
	GLint *const len,
	char *const data)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetProgramInfoLog failed"),
		sge::renderer::glsl::exception
	)

	glGetProgramInfoLog(
		program,
		maxlen,
		len,
		data
	);
}
