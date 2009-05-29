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
#include "../../check_state.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/text.hpp>

template<>
sge::ogl::glsl::traits<true>::handle
sge::ogl::glsl::create_program<true>()
{
	traits<true>::handle const ret(
		glCreateProgram()
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glCreateProgram failed"),
		sge::renderer::glsl::exception
	)

	return ret;
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
	glDetachShader(program, shader);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glDetachShader failed"),
		sge::renderer::glsl::exception
	)
}

template<>
void sge::ogl::glsl::delete_program<true>(
	traits<true>::handle const program)
{
	glDeleteProgram(program);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glDeleteProgram failed"),
		sge::renderer::glsl::exception
	)
}

template<>
void sge::ogl::glsl::attach_shader<true>(
	traits<true>::handle const program,
	traits<true>::handle const shader)
{
	glAttachShader(program, shader);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glAttachShader failed"),
		sge::renderer::glsl::exception
	)
}

template<>
void sge::ogl::glsl::link_program<true>(
	traits<true>::handle const program)
{
	glLinkProgram(program);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glLinKProgram failed"),
		sge::renderer::glsl::exception
	)
}

template<>
GLint sge::ogl::glsl::program_integer<true>(
	GLenum const what,
	traits<true>::handle const program)
{
	GLint result;

	glGetProgramiv(program, what, &result);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glGetProgramiv failed"),
		sge::renderer::glsl::exception
	)

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
	glUseProgram(program);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glUseProgram failed"),
		sge::renderer::glsl::exception
	)
}

template<>
void sge::ogl::glsl::program_info_log<true>(
	traits<true>::handle const program,
	GLint const maxlen,
	GLint *const len,
	char *const data)
{
	glGetProgramInfoLog(
		program,
		maxlen,
		len,
		data
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glGetProgramInfoLog failed"),
		sge::renderer::glsl::exception
	)
}
