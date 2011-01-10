/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../../../context/make_id.hpp"
#include "../../../common.hpp"

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
	uniform_1iv_(
		glUniform1iv
	),
	uniform_2iv_(
		glUniform2iv
	),
	uniform_3iv_(
		glUniform3iv
	),
	uniform_4iv_(
		glUniform4iv
	),
	uniform_1fv_(
		glUniform1fv
	),
	uniform_2fv_(
		glUniform2fv
	),
	uniform_3fv_(
		glUniform3fv
	),
	uniform_4fv_(
		glUniform4fv
	),
	uniform_matrix_2fv_(
		glUniformMatrix2fv
	),
	uniform_matrix_3fv_(
		glUniformMatrix3fv
	),
	uniform_matrix_4fv_(
		glUniformMatrix4fv
	),
	uniform_matrix_2x3fv_(
		glUniformMatrix2x3fv
	),
	uniform_matrix_3x2fv_(
		glUniformMatrix3x2fv
	),
	uniform_matrix_2x4fv_(
		glUniformMatrix2x4fv
	),
	uniform_matrix_4x2fv_(
		glUniformMatrix4x2fv
	),
	uniform_matrix_3x4fv_(
		glUniformMatrix3x4fv
	),
	uniform_matrix_4x3fv_(
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

PFNGLUNIFORM1IVPROC
sge::opengl::glsl::native::uniform_context::uniform_1iv() const
{
	return uniform_1iv_;
}
	
PFNGLUNIFORM2IVPROC
sge::opengl::glsl::native::uniform_context::uniform_2iv() const
{
	return uniform_2iv_;
}

PFNGLUNIFORM3IVPROC
sge::opengl::glsl::native::uniform_context::uniform_3iv() const
{
	return uniform_3iv_;
}

PFNGLUNIFORM4IVPROC
sge::opengl::glsl::native::uniform_context::uniform_4iv() const
{
	return uniform_4iv_;
}

PFNGLUNIFORM1FVPROC
sge::opengl::glsl::native::uniform_context::uniform_1fv() const
{
	return uniform_1fv_;
}

PFNGLUNIFORM2FVPROC
sge::opengl::glsl::native::uniform_context::uniform_2fv() const
{
	return uniform_2fv_;
}

PFNGLUNIFORM3FVPROC
sge::opengl::glsl::native::uniform_context::uniform_3fv() const
{
	return uniform_3fv_;
}

PFNGLUNIFORM3FVPROC
sge::opengl::glsl::native::uniform_context::uniform_4fv() const
{
	return uniform_4fv_;
}

PFNGLUNIFORMMATRIX2FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_2fv() const
{
	return uniform_matrix_2fv_;
}
	
PFNGLUNIFORMMATRIX3FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_3fv() const
{
	return uniform_matrix_3fv_;
}

PFNGLUNIFORMMATRIX4FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_4fv() const
{
	return uniform_matrix_4fv_;
}

PFNGLUNIFORMMATRIX2X3FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_2x3fv() const
{
	return uniform_matrix_2x3fv_;
}

PFNGLUNIFORMMATRIX3X2FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_3x2fv() const
{
	return uniform_matrix_3x2fv_;
}

PFNGLUNIFORMMATRIX2X4FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_2x4fv() const
{
	return uniform_matrix_2x4fv_;
}

PFNGLUNIFORMMATRIX4X2FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_4x2fv() const
{
	return uniform_matrix_4x2fv_;
}

PFNGLUNIFORMMATRIX3X4FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_3x4fv() const
{
	return uniform_matrix_3x4fv_;
}

PFNGLUNIFORMMATRIX4X3FVPROC
sge::opengl::glsl::native::uniform_context::uniform_matrix_4x3fv() const
{
	return uniform_matrix_4x3fv_;
}

sge::opengl::context::id const
sge::opengl::glsl::native::uniform_context::static_id(
	sge::opengl::context::make_id()
);
