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


#include "../attribute_setter.hpp"
#include "../init.hpp"
#include <sge/once.hpp>

namespace
{

//PFNGLVERTEXATTRIB1IPROC vertex_attrib_i1;
PFNGLVERTEXATTRIB1FPROC vertex_attrib_1f;
PFNGLVERTEXATTRIB2FVPROC vertex_attrib_2fv;
PFNGLVERTEXATTRIB3FVPROC vertex_attrib_3fv;
PFNGLVERTEXATTRIB4FVPROC vertex_attrib_4fv;

void initialize_attribute_setter();

}


sge::ogl::glsl::attribute_setter::attribute_setter(
	GLint const location)
:
	location(location)
{
	initialize_attribute_setter();
}
	
sge::ogl::glsl::attribute_type::type
sge::ogl::glsl::attribute_setter::operator()(
	renderer::glsl::int_type const i) const
{
	//vertex_attrib_1i(location, i);
	return attribute_type::int1;
}
	
sge::ogl::glsl::attribute_type::type
sge::ogl::glsl::attribute_setter::operator()(
	space_unit const f) const
{
	vertex_attrib_1f(location, f);
	return attribute_type::float1;
}

sge::ogl::glsl::attribute_type::type
sge::ogl::glsl::attribute_setter::operator()(
	math::vector2 const &v) const
{
	vertex_attrib_2fv(location, v.data());
	return attribute_type::float2;
}

sge::ogl::glsl::attribute_type::type
sge::ogl::glsl::attribute_setter::operator()(
	math::vector3 const &v) const
{
	vertex_attrib_3fv(location, v.data());
	return attribute_type::float3;
}

sge::ogl::glsl::attribute_type::type
sge::ogl::glsl::attribute_setter::operator()(
	math::vector4 const &v) const
{
	vertex_attrib_4fv(location, v.data());
	return attribute_type::float4;
}

namespace
{

void initialize_attribute_setter()
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
