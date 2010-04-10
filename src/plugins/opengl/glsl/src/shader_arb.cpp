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
#include "../../check_state.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>

template<>
sge::opengl::glsl::traits<false>::handle
sge::opengl::glsl::create_shader<false>(
	GLenum const type)
{
	traits<false>::handle const ret(
		glCreateShaderObjectARB(
			type
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glCreateShaderObjectARB failed"),
		sge::renderer::glsl::exception
	)

	return ret;
}

template<>
void sge::opengl::glsl::shader_source<false>(
	traits<false>::handle const shader,
	GLint const num_strings,
	char const **const strings,
	GLint const *const len_of_strings)
{
	glShaderSourceARB(
		shader,
		num_strings,
		strings,
		len_of_strings
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glShaderSourceARB"),
		sge::renderer::glsl::exception
	)
}

template<>
void sge::opengl::glsl::compile_shader<false>(
	traits<false>::handle const shader)
{
	glCompileShaderARB(shader);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glCompileShaderARB failed"),
		sge::renderer::glsl::exception
	)
}

template<>
GLint sge::opengl::glsl::shader_integer<false>(
	GLenum const what,
	traits<false>::handle const shader
)
{
	GLint result;

	glGetObjectParameterivARB(
		shader,
		what,
		&result
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetObjectParameterivARB"),
		sge::renderer::glsl::exception
	)

	return result;
}

template<>
GLint sge::opengl::glsl::compile_status<false>(
	traits<false>::handle const shader
)
{
	return shader_integer<false>(
		GL_OBJECT_COMPILE_STATUS_ARB,
		shader
	);
}

template<>
void sge::opengl::glsl::shader_info_log<false>(
	traits<false>::handle const shader,
	GLint const maxlen,
	GLint *const len,
	char *const data
)
{
	glGetInfoLogARB(
		shader,
		maxlen,
		len,
		data
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetInfoLogARB failed"),
		sge::renderer::glsl::exception
	)
}

template<>
void sge::opengl::glsl::delete_shader<false>(
	traits<false>::handle const shader)
{
	glDeleteObjectARB(shader);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDeleteObjectARB failed"),
		sge::renderer::glsl::exception
	)
}

template<>
GLint
sge::opengl::glsl::shader_info_log_length<false>(
	traits<false>::handle const shader
)
{
	return
		shader_integer<false>(
			GL_OBJECT_INFO_LOG_LENGTH_ARB,
			shader
		);
}
