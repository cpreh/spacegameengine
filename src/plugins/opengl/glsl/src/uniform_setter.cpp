/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../uniform_setter.hpp"
#include "../init.hpp"
#include <sge/renderer/matrix_convert.hpp>
#include <sge/renderer/vector_convert.hpp>
#include <sge/renderer/arithmetic_convert.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/once.hpp>

namespace
{

PFNGLUNIFORM1IPROC uniform_1i;
PFNGLUNIFORM1FPROC uniform_1f;
PFNGLUNIFORM2FVPROC uniform_2fv;
PFNGLUNIFORM3FVPROC uniform_3fv;
PFNGLUNIFORM3FVPROC uniform_4fv;
PFNGLUNIFORMMATRIX4FVPROC uniform_matrix_4fv;

void initialize_uniform_setter();

}

sge::ogl::glsl::uniform_setter::uniform_setter(
	GLint const location)
:
	location(location)
{
	initialize_uniform_setter();
}
	
sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::int_type const i) const
{
	uniform_1i(location, i);
	return uniform_type::int1;
}
	
sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::any_arithmetic const &f) const
{
	uniform_1f(
		location,
		renderer::arithmetic_convert<GLfloat>(f));
	return uniform_type::float1;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::any_vector2 const &v) const
{
	uniform_2fv(
		location,
		1u,
		renderer::vector_convert<
			math::basic_vector<GLfloat, 2>
		>(
			v).data());
	return uniform_type::float2;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::any_vector3 const &v) const
{
	uniform_3fv(
		location,
		1u,
		renderer::vector_convert<
			math::basic_vector<GLfloat, 3>
		>(
			v).data());
	return uniform_type::float3;
}
	
sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::any_vector4 const &v) const
{
	uniform_4fv(
		location,
		1u,
		renderer::vector_convert<
			math::basic_vector<GLfloat, 4>
		>(
			v).data());
	return uniform_type::float4;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::any_matrix const &m) const
{
	uniform_matrix_4fv(
		location,
		1u,
		false,
		renderer::matrix_convert<
			math::basic_matrix<GLfloat, 4, 4>
		>(
			m).data());
	return uniform_type::matrix4x4;
}

namespace
{

void initialize_uniform_setter()
{
	SGE_FUNCTION_ONCE
	if(sge::ogl::glsl::is_native())
	{
		uniform_1i = glUniform1i;
		uniform_1f = glUniform1f;
		uniform_2fv = glUniform2fv;
		uniform_3fv = glUniform3fv;
		uniform_4fv = glUniform4fv;
		uniform_matrix_4fv = glUniformMatrix4fv;
	}
	else
	{
		uniform_1i = glUniform1iARB;
		uniform_1f = glUniform1fARB;
		uniform_2fv = glUniform2fvARB;
		uniform_3fv = glUniform3fvARB;
		uniform_4fv = glUniform4fvARB;
		uniform_matrix_4fv = glUniformMatrix4fvARB;

	}
}

}
