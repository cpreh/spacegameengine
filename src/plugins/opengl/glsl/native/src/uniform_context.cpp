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


#include "../uniform_context.hpp"

sge::opengl::glsl::native::uniform_context::uniform_context()
:
	get_uniform_location_(
		glGetUniformLocation
	),
	get_uniform_iv_(
		glGetUniformiv
	),
	get_uniform_fv_(
		glGetUniformfv
	),
	uniform_1iv(
		glUniform1iv
	),
	uniform_2iv(
		glUniform2iv
	),
	uniform_3iv(
		glUniform3iv
	),
	uniform_4iv(
		glUniform4iv
	),
	uniform_1fv(
		glUniform1fv
	),
	uniform_2fv(
		glUniform2fv
	),
	uniform_3fv(
		glUniform3fv
	),
	uniform_4fv(
		glUniform4fv
	),
	uniform_matrix_2fv(
		glUniformMatrix2fv
	),
	uniform_matrix_3fv(
		glUniformMatrix3fv
	),
	uniform_matrix_4fv(
		glUniformMatrix4fv
	),
	uniform_matrix_2x3fv(
		glUniformMatrix2x3fv
	),
	uniform_matrix_3x2fv(
		glUniformMatrix3x2fv
	),
	uniform_matrix_2x4fv(
		glUniformMatrix2x4fv
	),
	uniform_matrix_4x2fv(
		glUniformMatrix4x2fv
	),
	uniform_matrix_3x4fv(
		glUniformMatrix3x4fv
	),
	uniform_matrix_4x3fv(
		glUniformMatrix4x3fv
	)
{}

sge::opengl::glsl::native::uniform_context::~uniform_context()
{
}

PFNGLGETUNIFORMLOCATIONPROC
sge::opengl::glsl::native::uniform_context::get_uniform_location() const
{
	return get_uniform_location_;
}

PFNGLGETUNIFORMIVPROC
sge::opengl::glsl::native::uniform_context::get_uniform_iv() const
{
	return get_uniform_iv_;
}

PFNGLGETUNIFORMFVPROC
sge::opengl::glsl::native::uniform_context::get_uniform_fv() const
{
	return get_uniform_fv_;
}


#if 0
namespace
{

template<>
sge::opengl::glsl::traits<false>::handle
location_impl(
	typename sge::opengl::glsl::traits<false>::handle const _program
	char const *const _name
)
{
	return
		glGetUniformLocationARB(
			_program,
			_name
		);
}

}
PFNGLGETUNIFORMIVPROC
get_uniform_iv<false>::get()
{
	return glGetUniformivARB;
}

PFNGLGETUNIFORMFVPROC
get_uniform_fv<false>::get()
{
	return glGetUniformfvARB;
}


#endif


