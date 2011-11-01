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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glsl/arb/uniform_context.hpp>


sge::opengl::glsl::arb::uniform_context::uniform_context()
:
	get_uniform_location_(
		glGetUniformLocationARB
	),
	get_uniform_iv_(
		glGetUniformivARB
	),
	get_uniform_fv_(
		glGetUniformfvARB
	),
	uniform_1iv_(
		glUniform1ivARB
	),
	uniform_2iv_(
		glUniform2ivARB
	),
	uniform_3iv_(
		glUniform3ivARB
	),
	uniform_4iv_(
		glUniform4ivARB
	),
	uniform_1fv_(
		glUniform1fvARB
	),
	uniform_2fv_(
		glUniform2fvARB
	),
	uniform_3fv_(
		glUniform3fvARB
	),
	uniform_4fv_(
		glUniform4fvARB
	),
	uniform_matrix_2fv_(
		glUniformMatrix2fvARB
	),
	uniform_matrix_3fv_(
		glUniformMatrix3fvARB
	),
	uniform_matrix_4fv_(
		glUniformMatrix4fvARB
	)
{}

sge::opengl::glsl::arb::uniform_context::~uniform_context()
{
}

PFNGLGETUNIFORMLOCATIONARBPROC
sge::opengl::glsl::arb::uniform_context::get_uniform_location() const
{
	return get_uniform_location_;
}

PFNGLGETUNIFORMIVARBPROC
sge::opengl::glsl::arb::uniform_context::get_uniform_iv() const
{
	return get_uniform_iv_;
}

PFNGLGETUNIFORMFVARBPROC
sge::opengl::glsl::arb::uniform_context::get_uniform_fv() const
{
	return get_uniform_fv_;
}

PFNGLUNIFORM1IVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_1iv() const
{
	return uniform_1iv_;
}

PFNGLUNIFORM2IVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_2iv() const
{
	return uniform_2iv_;
}

PFNGLUNIFORM3IVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_3iv() const
{
	return uniform_3iv_;
}

PFNGLUNIFORM4IVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_4iv() const
{
	return uniform_4iv_;
}

PFNGLUNIFORM1FVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_1fv() const
{
	return uniform_1fv_;
}

PFNGLUNIFORM2FVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_2fv() const
{
	return uniform_2fv_;
}

PFNGLUNIFORM3FVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_3fv() const
{
	return uniform_3fv_;
}

PFNGLUNIFORM4FVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_4fv() const
{
	return uniform_4fv_;
}

PFNGLUNIFORMMATRIX2FVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_matrix_2fv() const
{
	return uniform_matrix_2fv_;
}

PFNGLUNIFORMMATRIX3FVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_matrix_3fv() const
{
	return uniform_matrix_3fv_;
}

PFNGLUNIFORMMATRIX4FVARBPROC
sge::opengl::glsl::arb::uniform_context::uniform_matrix_4fv() const
{
	return uniform_matrix_4fv_;
}

sge::opengl::context::id const
sge::opengl::glsl::arb::uniform_context::static_id(
	sge::opengl::context::make_id()
);
