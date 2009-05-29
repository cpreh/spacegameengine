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
#include "../../sentry.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/text.hpp>

template<>
sge::ogl::glsl::traits<true>::handle
sge::ogl::glsl::create_shader<true>(
	GLenum const type)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glCreateShader failed"),
		sge::renderer::glsl::exception
	)

	return glCreateShader(type);
}

template<>
void sge::ogl::glsl::shader_source<true>(
	traits<true>::handle const shader,
	GLint const num_strings,
	char const **const strings,
	GLint const *const len_of_strings)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glShaderSource failed"),
		sge::renderer::glsl::exception
	)

	glShaderSource(
		shader,
		num_strings,
		strings,
		len_of_strings
	);
}

template<>
void sge::ogl::glsl::compile_shader<true>(
	traits<true>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glCompileShader failed"),
		sge::renderer::glsl::exception
	)

	glCompileShader(shader);
}

template<>
GLint sge::ogl::glsl::shader_integer<true>(
	GLenum const what,
	traits<true>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetShaderiv failed"),
		sge::renderer::glsl::exception
	)

	GLint result;
	glGetShaderiv(shader, what, &result);
	return result;
}

template<>
GLint sge::ogl::glsl::compile_status<true>(
	traits<true>::handle const shader)
{
	return shader_integer<true>(
		GL_COMPILE_STATUS,
		shader
	);
}

template<>
void sge::ogl::glsl::shader_info_log<true>(
	traits<true>::handle const shader,
	GLint const maxlen,
	GLint *const len,
	char *const data)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetShaderInfoLog failed"),
		sge::renderer::glsl::exception
	)

	glGetShaderInfoLog(
		shader,
		maxlen,
		len,
		data
	);
}

template<>
void sge::ogl::glsl::delete_shader<true>(
	traits<true>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glDeleteShader failed"),
		sge::renderer::glsl::exception
	)

	glDeleteShader(shader);
}
