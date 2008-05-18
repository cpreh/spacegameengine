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


#include "../attribute_variable.hpp"

template<bool Native>
sge::ogl::glsl::attribute_variable<Native>::attribute_variable(
	const handle program,
	const std::string& name)
: ref(glGetAttribLocation(program, name.c_str()))
{}

template<bool Native>
void sge::ogl::glsl::attribute_variable<Native>::set(const space_unit f)
{
	glVertexAttrib1f(location(), f);	
}

template<bool Native>
void sge::ogl::glsl::attribute_variable<Native>::set(const math::vector2& v)
{
	glVertexAttrib2fv(location(), v.data());
}

template<bool Native>
void sge::ogl::glsl::attribute_variable<Native>::set(const math::vector3& v)
{
	glVertexAttrib3fv(location(), v.data());
}

template<bool Native>
void sge::ogl::glsl::attribute_variable<Native>::set(const math::vector4& v)
{
	glVertexAttrib4fv(location(), v.data());
}

template<bool Native>
GLint sge::ogl::glsl::attribute_variable<Native>::location() const
{
	return ref;
}

template class sge::ogl::glsl::attribute_variable<true>;
template class sge::ogl::glsl::attribute_variable<false>;
