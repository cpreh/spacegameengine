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
#include "../../sentry.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/text.hpp>

template<>
sge::ogl::glsl::traits<false>::handle
sge::ogl::glsl::create_program<false>()
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glCreateProgramObjectARB"),
		sge::renderer::glsl::exception
	)

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
	traits<false>::handle const program,
	traits<false>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glDetachObjectARB failed"),
		sge::renderer::glsl::exception
	)

	glDetachObjectARB(program, shader);
}

template<>
void sge::ogl::glsl::delete_program<false>(
	traits<false>::handle const program)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glDeleteObjectARB failed"),
		sge::renderer::glsl::exception
	)

	glDeleteObjectARB(program);
}

template<>
void sge::ogl::glsl::attach_shader<false>(
	traits<false>::handle const program,
	traits<false>::handle const shader)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glAttachObjectARB"),
		sge::renderer::glsl::exception
	)

	glAttachObjectARB(program, shader);
}

template<>
void sge::ogl::glsl::link_program<false>(
	traits<false>::handle const program)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glLinkProgramARB failed"),
		sge::renderer::glsl::exception
	)

	glLinkProgramARB(program);
}

template<>
GLint sge::ogl::glsl::program_integer<false>(
	GLenum const what,
	traits<false>::handle const program)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetObjectParameterivARB failed"),
		sge::renderer::glsl::exception
	)

	GLint result;
	glGetObjectParameterivARB(program, what, &result);
	return result;
}

template<>
GLint sge::ogl::glsl::link_status<false>(
	traits<false>::handle const program)
{
	return program_integer<false>(
		GL_OBJECT_LINK_STATUS_ARB,
		program);
}

template<>
void sge::ogl::glsl::use_program<false>(
	traits<false>::handle const program)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glUseProgramObjectARB failed"),
		sge::renderer::glsl::exception
	)

	glUseProgramObjectARB(program);
}

template<>
void sge::ogl::glsl::program_info_log<false>(
	traits<false>::handle const program,
	GLint const maxlen,
	GLint *const len,
	char *const data)
{
	SGE_OPENGL_SENTRY(
		SGE_TEXT("glGetInfoLogARB failed"),
		sge::renderer::glsl::exception
	)

	glGetInfoLogARB(
		program,
		maxlen,
		len,
		data
	);
}
