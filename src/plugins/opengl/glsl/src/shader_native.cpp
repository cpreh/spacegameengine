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


#include "../shader_native.hpp"
#include "../../check_state.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>

template<>
sge::opengl::glsl::traits<true>::handle
sge::opengl::glsl::create_shader<true>(
	GLenum const type)
{
	traits<true>::handle const ret(
		glCreateShader(
			type
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glCreateShader failed"),
		sge::renderer::glsl::exception
	)

	return ret;
}

template<>
void sge::opengl::glsl::shader_source<true>(
	traits<true>::handle const shader,
	GLint const num_strings,
	char const **const strings,
	GLint const *const len_of_strings)
{
	glShaderSource(
		shader,
		num_strings,
		strings,
		len_of_strings
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glShaderSource failed"),
		sge::renderer::glsl::exception
	)
}

template<>
void sge::opengl::glsl::compile_shader<true>(
	traits<true>::handle const shader)
{
	glCompileShader(shader);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glCompileShader failed"),
		sge::renderer::glsl::exception
	)
}

template<>
GLint sge::opengl::glsl::shader_integer<true>(
	GLenum const what,
	traits<true>::handle const shader)
{
	GLint result;

	glGetShaderiv(shader, what, &result);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetShaderiv failed"),
		sge::renderer::glsl::exception
	)

	return result;
}

template<>
GLint sge::opengl::glsl::compile_status<true>(
	traits<true>::handle const shader)
{
	return shader_integer<true>(
		GL_COMPILE_STATUS,
		shader
	);
}

template<>
void sge::opengl::glsl::shader_info_log<true>(
	traits<true>::handle const shader,
	GLint const maxlen,
	GLint *const len,
	char *const data)
{
	glGetShaderInfoLog(
		shader,
		maxlen,
		len,
		data
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetShaderInfoLog failed"),
		sge::renderer::glsl::exception
	)
}

template<>
void sge::opengl::glsl::delete_shader<true>(
	traits<true>::handle const shader)
{
	glDeleteShader(shader);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDeleteShader failed"),
		sge::renderer::glsl::exception
	)
}
