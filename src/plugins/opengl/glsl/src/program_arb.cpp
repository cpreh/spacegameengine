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



#include "../program_arb.hpp"
#include "../../error.hpp"

template<>
sge::ogl::glsl::traits<false>::handle
sge::ogl::glsl::create_program<false>()
{
	SGE_OPENGL_SENTRY
	return glCreateProgramObjectARB();
}

template<>
GLenum 
sge::ogl::glsl::vertex_shader_type<false>()
{
	return GL_VERTEX_SHADER_ARB;
}

template<>
GLenum 
sge::ogl::glsl::pixel_shader_type<false>()
{
	return GL_FRAGMENT_SHADER_ARB;
}

template<>
void sge::ogl::glsl::detach_shader<false>(
	const traits<false>::handle program,
	const traits<false>::handle shader)
{
	SGE_OPENGL_SENTRY
	glDetachObjectARB(program, shader);
}

template<>
void sge::ogl::glsl::delete_program<false>(
	const traits<false>::handle program)
{
	SGE_OPENGL_SENTRY
	glDeleteObjectARB(program);
}

template<>
void sge::ogl::glsl::attach_shader<false>(
	const traits<false>::handle program,
	const traits<false>::handle shader)
{
	SGE_OPENGL_SENTRY
	glAttachObjectARB(program, shader);
}

template<>
void sge::ogl::glsl::link_program<false>(
	const traits<false>::handle program)
{
	SGE_OPENGL_SENTRY
	glLinkProgramARB(program);
}

template<>
GLint sge::ogl::glsl::program_integer<false>(
	const GLenum what,
	const traits<false>::handle program)
{
	SGE_OPENGL_SENTRY
	GLint result;
	glGetObjectParameterivARB(program, what, &result);
	return result;
}

template<>
GLint sge::ogl::glsl::link_status<false>(
	const traits<false>::handle program)
{
	return program_integer<false>(
		GL_OBJECT_LINK_STATUS_ARB,
		program);
}

template<>
void sge::ogl::glsl::use_program<false>(
	const traits<false>::handle program)
{
	SGE_OPENGL_SENTRY
	glUseProgramObjectARB(program);
}

template<>
void sge::ogl::glsl::program_info_log<false>(
	const traits<false>::handle program,
	const GLint maxlen,
	GLint *const len,
	char *const data)
{
	SGE_OPENGL_SENTRY
	glGetInfoLogARB(
		program,
		maxlen,
		len,
		data);
}
