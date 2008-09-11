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
#include "../attribute_variable_functions.hpp"
#include "../init.hpp"
#include "../../error.hpp"
#include <sge/once.hpp>

namespace
{

PFNGLVERTEXATTRIB1FPROC vertex_attrib_1f;
PFNGLVERTEXATTRIB2FVPROC vertex_attrib_2fv;
PFNGLVERTEXATTRIB3FVPROC vertex_attrib_3fv;
PFNGLVERTEXATTRIB4FVPROC vertex_attrib_4fv;

void initialize_attribute_variable();

}

template<bool Native>
sge::ogl::glsl::attribute_variable<Native>::attribute_variable(
	handle const program,
	renderer::glsl::string const &name)
:
	ref(
		get_attrib_location<Native>(
			program,
			name.c_str()))
{}

template<bool Native>
void sge::ogl::glsl::attribute_variable<Native>::set(const space_unit f)
{
	SGE_OPENGL_SENTRY
	vertex_attrib_1f(location(), f);	
}

template<bool Native>
void sge::ogl::glsl::attribute_variable<Native>::set(const math::vector2& v)
{
	SGE_OPENGL_SENTRY
	vertex_attrib_2fv(location(), v.data());
}

template<bool Native>
void sge::ogl::glsl::attribute_variable<Native>::set(const math::vector3& v)
{
	SGE_OPENGL_SENTRY
	vertex_attrib_3fv(location(), v.data());
}

template<bool Native>
void sge::ogl::glsl::attribute_variable<Native>::set(const math::vector4& v)
{
	SGE_OPENGL_SENTRY
	vertex_attrib_4fv(location(), v.data());
}

template<bool Native>
GLint sge::ogl::glsl::attribute_variable<Native>::location() const
{
	return ref;
}

template class sge::ogl::glsl::attribute_variable<true>;
template class sge::ogl::glsl::attribute_variable<false>;

namespace
{

void initialize_attribute_varaible()
{
	SGE_FUNCTION_ONCE
	if(sge::ogl::glsl::is_native())
	{
		vertex_attrib_1f = glVertexAttrib1f;
		vertex_attrib_2fv = glVertexAttrib2fv;
		vertex_attrib_3fv = glVertexAttrib3fv;
		vertex_attrib_4fv = glVertexAttrib4fv;
	}
	else
	{
		vertex_attrib_1f = glVertexAttrib1fARB;
		vertex_attrib_2fv = glVertexAttrib2fvARB;
		vertex_attrib_3fv = glVertexAttrib3fvARB;
		vertex_attrib_4fv = glVertexAttrib4fvARB;
	}
}

}
