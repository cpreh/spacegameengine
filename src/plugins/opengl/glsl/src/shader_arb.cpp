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
#include "../../error.hpp"

template<>
sge::ogl::glsl::traits<false>::handle
sge::ogl::glsl::create_shader<false>(
	const GLenum type)
{
	SGE_OPENGL_SENTRY
	return glCreateShaderObjectARB(type);
}

template<>
void sge::ogl::glsl::shader_source<false>(
	const traits<false>::handle shader,
	const GLint num_strings,
	char const **const strings,
	GLint const *const len_of_strings)
{
	SGE_OPENGL_SENTRY
	glShaderSourceARB(
		shader,
		num_strings,
		strings,
		len_of_strings);
}

template<>
void sge::ogl::glsl::compile_shader<false>(
	const traits<false>::handle shader)
{
	SGE_OPENGL_SENTRY
	glCompileShaderARB(shader);
}

template<>
GLint sge::ogl::glsl::shader_integer<false>(
	const GLenum what,
	const traits<false>::handle shader)
{
	SGE_OPENGL_SENTRY
	GLint result;
	glGetObjectParameterivARB(shader, what, &result);
	return result;
}

template<>
GLint sge::ogl::glsl::compile_status<false>(
	const traits<false>::handle shader)
{
	return shader_integer<false>(
		GL_OBJECT_COMPILE_STATUS_ARB,
		shader);
}

template<>
void sge::ogl::glsl::shader_info_log<false>(
	const traits<false>::handle shader,
	const GLint maxlen,
	GLint *const len,
	char *const data)
{
	SGE_OPENGL_SENTRY
	glGetInfoLogARB(
		shader,
		maxlen,
		len,
		data);
}

template<>
void sge::ogl::glsl::delete_shader<false>(
	const traits<false>::handle shader)
{
	SGE_OPENGL_SENTRY
	glDeleteObjectARB(shader);
}
