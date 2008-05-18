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
#include <sge/math/matrix_impl.hpp>

template<bool Native>
sge::ogl::glsl::uniform_variable<Native>::uniform_variable(
	const handle program,
	const std::string& name)
: ref(glGetUniformLocation(program, name.c_str()))
{}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const space_unit f)
{
	glUniform1f(location(), f);	
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const math::vector2& v)
{
	glUniform2fv(location(), static_cast<GLsizei>(v.size()), v.data());
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const math::vector3& v)
{
	glUniform3fv(location(), static_cast<GLsizei>(v.size()), v.data());
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const math::vector4& v)
{
	glUniform4fv(location(), static_cast<GLsizei>(v.size()), v.data());
}

template<bool Native>
void sge::ogl::glsl::uniform_variable<Native>::set(const math::space_matrix& m)
{
	glUniformMatrix4fv(location(), static_cast<GLsizei>(m.size()), false, m.data());
}

template<bool Native>
GLint sge::ogl::glsl::uniform_variable<Native>::location() const
{
	return ref;
}

template class sge::ogl::glsl::uniform_variable<true>;
template class sge::ogl::glsl::uniform_variable<false>;
