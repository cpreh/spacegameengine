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


#include "../uniform_variable.hpp"
#include "../uniform_variable_functions.hpp"
#include "../init.hpp"
#include "../../error.hpp"
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

void initialize_uniform_variable();

}

template<bool Native>
sge::ogl::glsl::uniform_variable<Native>::uniform_variable(
	const handle program,
	std::string const &name)
: ref(get_uniform_location<Native>(program, name.c_str()))
{
	initialize_uniform_variable();
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(
	int const i)
{
	SGE_OPENGL_SENTRY
	uniform_1i(location(), i);
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const space_unit f)
{
	SGE_OPENGL_SENTRY
	uniform_1f(location(), f);	
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const math::vector2& v)
{
	SGE_OPENGL_SENTRY
	uniform_2fv(location(), static_cast<GLsizei>(1), v.data());
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const math::vector3& v)
{
	SGE_OPENGL_SENTRY
	uniform_3fv(location(), static_cast<GLsizei>(1), v.data());
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const math::vector4& v)
{
	SGE_OPENGL_SENTRY
	uniform_4fv(location(), static_cast<GLsizei>(1), v.data());
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const math::space_matrix& m)
{
	SGE_OPENGL_SENTRY
	uniform_matrix_4fv(location(), static_cast<GLsizei>(1), false, m.data());
}

template<bool Native>
GLint sge::ogl::glsl::uniform_variable<Native>::location() const
{
	return ref;
}

template class sge::ogl::glsl::uniform_variable<true>;
template class sge::ogl::glsl::uniform_variable<false>;

namespace
{

void initialize_uniform_variable()
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
