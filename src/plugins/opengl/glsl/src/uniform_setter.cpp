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
#include <sge/array_wrapper_impl.hpp>
#include <sge/once.hpp>
#include <sge/raw_vector_impl.hpp>

namespace
{

PFNGLUNIFORM1IPROC uniform_1i;
PFNGLUNIFORM1IVPROC uniform_1iv;
PFNGLUNIFORM1FPROC uniform_1f;
PFNGLUNIFORM1FVPROC uniform_1fv;
PFNGLUNIFORM2FVPROC uniform_2fv;
PFNGLUNIFORM3FVPROC uniform_3fv;
PFNGLUNIFORM3FVPROC uniform_4fv;
PFNGLUNIFORMMATRIX4FVPROC uniform_matrix_4fv;

void initialize_uniform_setter();

template<
	typename Dest,
	typename T
>
sge::raw_vector<Dest> const
convert_array(
	sge::array_wrapper<T> const &);

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
	renderer::glsl::float_type const &f) const
{
	uniform_1f(
		location,
		f);
	return uniform_type::float1;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::vector2 const &v) const
{
	uniform_2fv(
		location,
		1u,
		v.data());
	return uniform_type::float2;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::vector3 const &v) const
{
	uniform_3fv(
		location,
		1u,
		v.data());
	return uniform_type::float3;
}
	
sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::vector4 const &v) const
{
	uniform_4fv(
		location,
		1u,
		v.data());
	return uniform_type::float4;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::matrix4x4 const &m) const
{
	uniform_matrix_4fv(
		location,
		1u,
		false,
		m.data());
	return uniform_type::matrix4x4;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::int_type> const &m) const
{
	uniform_1iv(
		location,
		static_cast<GLsizei>(m.size()),
		m.data());
	return uniform_type::int1_array;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::float_type> const &m) const
{
	uniform_1fv(
		location,
		static_cast<GLsizei>(m.size()),
		m.data());
	return uniform_type::float1_array;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::vector2> const &a) const
{
	uniform_2fv(
		location,
		static_cast<GLsizei>(a.size()),
		convert_array<
			GLfloat
		>(a).data());
	return uniform_type::float2_array;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::vector3> const &a) const
{
	uniform_3fv(
		location,
		static_cast<GLsizei>(a.size()),
		convert_array<
			GLfloat
		>(a).data());
	return uniform_type::float3_array;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::vector4> const &a) const
{
	uniform_4fv(
		location,
		static_cast<GLsizei>(a.size()),
		convert_array<
			GLfloat
		>(a).data());
	return uniform_type::float4_array;
}

sge::ogl::glsl::uniform_type::type
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::matrix4x4> const &a) const
{
	uniform_matrix_4fv(
		location,
		static_cast<GLsizei>(a.size()),
		false,
		convert_array<
			GLfloat
		>(a).data());
	return uniform_type::matrix4x4_array;
}

namespace
{

void initialize_uniform_setter()
{
	SGE_FUNCTION_ONCE
	if(sge::ogl::glsl::is_native())
	{
		uniform_1i = glUniform1i;
		uniform_1iv = glUniform1iv;
		uniform_1f = glUniform1f;
		uniform_1fv = glUniform1fv;
		uniform_2fv = glUniform2fv;
		uniform_3fv = glUniform3fv;
		uniform_4fv = glUniform4fv;
		uniform_matrix_4fv = glUniformMatrix4fv;
	}
	else
	{
		uniform_1i = glUniform1iARB;
		uniform_1iv = glUniform1ivARB;
		uniform_1f = glUniform1fARB;
		uniform_1fv = glUniform1fvARB;
		uniform_2fv = glUniform2fvARB;
		uniform_3fv = glUniform3fvARB;
		uniform_4fv = glUniform4fvARB;
		uniform_matrix_4fv = glUniformMatrix4fvARB;
	}
}

template<
	typename Dest,
	typename T
>
sge::raw_vector<Dest> const
convert_array(
	sge::array_wrapper<T> const &a)
{
	sge::raw_vector<Dest> ret;
	for(typename sge::array_wrapper<T>::iterator it(a.begin()); it != a.end(); ++it)
		ret.insert(ret.end(), it->begin(), it->end());
	return ret;
}

}
