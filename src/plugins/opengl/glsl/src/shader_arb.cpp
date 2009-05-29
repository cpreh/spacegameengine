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



#include "../shader_arb.hpp"
#include "../../sentry.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/text.hpp>

template<>
sge::ogl::glsl::traits<false>::handle
sge::ogl::glsl::create_shader<false>(
	GLenum const type)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glCreateShaderObjectARB failed"),
		sge::renderer::glsl::exception
	)

	return glCreateShaderObjectARB(type);
}

template<>
void sge::ogl::glsl::shader_source<false>(
	traits<false>::handle const shader,
	GLint const num_strings,
	char const **const strings,
	GLint const *const len_of_strings)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glShaderSourceARB"),
		sge::renderer::glsl::exception
	)

	glShaderSourceARB(
		shader,
		num_strings,
		strings,
		len_of_strings
	);
}

template<>
void sge::ogl::glsl::compile_shader<false>(
	traits<false>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glCompileShaderARB failed"),
		sge::renderer::glsl::exception
	)

	glCompileShaderARB(shader);
}

template<>
GLint sge::ogl::glsl::shader_integer<false>(
	GLenum const what,
	traits<false>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetObjectParameterivARB"),
		sge::renderer::glsl::exception
	)
		
	GLint result;
	glGetObjectParameterivARB(shader, what, &result);
	return result;
}

template<>
GLint sge::ogl::glsl::compile_status<false>(
	traits<false>::handle const shader)
{
	return shader_integer<false>(
		GL_OBJECT_COMPILE_STATUS_ARB,
		shader
	);
}

template<>
void sge::ogl::glsl::shader_info_log<false>(
	traits<false>::handle const shader,
	GLint const maxlen,
	GLint *const len,
	char *const data)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetInfoLogARB failed"),
		sge::renderer::glsl::exception
	)

	glGetInfoLogARB(
		shader,
		maxlen,
		len,
		data
	);
}

template<>
void sge::ogl::glsl::delete_shader<false>(
	traits<false>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glDeleteObjectARB failed"),
		sge::renderer::glsl::exception
	)

	glDeleteObjectARB(shader);
}
