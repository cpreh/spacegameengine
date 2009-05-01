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



#include "../../../error.hpp"
#include "../../init.hpp"
#include "../setter.hpp"
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/math/vector/dynamic_impl.hpp>
#include <sge/once.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

namespace
{

//PFNGLVERTEXATTRIB1IPROC vertex_attrib_i1;
PFNGLVERTEXATTRIB1FPROC vertex_attrib_1f;
PFNGLVERTEXATTRIB2FVPROC vertex_attrib_2fv;
PFNGLVERTEXATTRIB3FVPROC vertex_attrib_3fv;
PFNGLVERTEXATTRIB4FVPROC vertex_attrib_4fv;

PFNGLVERTEXATTRIB1DPROC vertex_attrib_1d;
PFNGLVERTEXATTRIB2DVPROC vertex_attrib_2dv;
PFNGLVERTEXATTRIB3DVPROC vertex_attrib_3dv;
PFNGLVERTEXATTRIB4DVPROC vertex_attrib_4dv;

void initialize_setter();

class arithmetic_visitor {
public:
	typedef sge::ogl::glsl::attribute::type::type result_type;

	explicit arithmetic_visitor(
		GLint location);
		
	result_type
	operator()(
		float) const;

	result_type
	operator()(
		double) const;
private:
	GLint const location;
};

class vector_visitor {
public:
	typedef sge::ogl::glsl::attribute::type::type result_type;

	explicit vector_visitor(
		GLint location);
	
	result_type
	operator()(
		sge::math::vector::dynamic<
			float
		>::type const &) const;
	
	result_type
	operator()(
		sge::math::vector::dynamic<
			double
		>::type const &) const;
private:
	GLint const location;
};

}


sge::ogl::glsl::attribute::setter::setter(
	GLint const location)
:
	location(location)
{
	initialize_setter();
}
	
sge::ogl::glsl::attribute::setter::result_type
sge::ogl::glsl::attribute::setter::operator()(
	renderer::any_arithmetic const &f) const
{
	return variant::apply_unary(
		arithmetic_visitor(
			location
		),
		f
	);
}

sge::ogl::glsl::attribute::setter::result_type
sge::ogl::glsl::attribute::setter::operator()(
	renderer::any_dynamic_vector const &v) const
{
	return variant::apply_unary(
		vector_visitor(
			location
		),
		v
	);
}

namespace
{

void initialize_setter()
{
	SGE_FUNCTION_ONCE
	if(sge::ogl::glsl::is_native())
	{
		vertex_attrib_1f = glVertexAttrib1f;
		vertex_attrib_2fv = glVertexAttrib2fv;
		vertex_attrib_3fv = glVertexAttrib3fv;
		vertex_attrib_4fv = glVertexAttrib4fv;
		vertex_attrib_1d = glVertexAttrib1d;
		vertex_attrib_2dv = glVertexAttrib2dv;
		vertex_attrib_3dv = glVertexAttrib3dv;
		vertex_attrib_4dv = glVertexAttrib4dv;
	}
	else
	{
		vertex_attrib_1f = glVertexAttrib1fARB;
		vertex_attrib_2fv = glVertexAttrib2fvARB;
		vertex_attrib_3fv = glVertexAttrib3fvARB;
		vertex_attrib_4fv = glVertexAttrib4fvARB;
		vertex_attrib_1d = glVertexAttrib1dARB;
		vertex_attrib_2dv = glVertexAttrib2dvARB;
		vertex_attrib_3dv = glVertexAttrib3dvARB;
		vertex_attrib_4dv = glVertexAttrib4dvARB;
	}
}

arithmetic_visitor::arithmetic_visitor(
	GLint const location)
:
	location(location)
{}

arithmetic_visitor::result_type
arithmetic_visitor::operator()(
	float const f) const
{
	SGE_OPENGL_SENTRY

	vertex_attrib_1f(location, f);
	return sge::ogl::glsl::attribute::type::float1;
}

arithmetic_visitor::result_type
arithmetic_visitor::operator()(
	double const d) const
{
	SGE_OPENGL_SENTRY

	vertex_attrib_1d(location, d);
	return sge::ogl::glsl::attribute::type::double1;
}


vector_visitor::vector_visitor(
	GLint const location)
:
	location(location)
{}
	
vector_visitor::result_type
vector_visitor::operator()(
	sge::math::vector::dynamic<
		float
	>::type const &v) const
{
	SGE_OPENGL_SENTRY

	switch(v.size()) {
	case 2:
		vertex_attrib_2fv(
			location,
			v.data());
		break;
	case 3:
		vertex_attrib_3fv(
			location,
			v.data());
		break;
	case 4:
		vertex_attrib_4fv(
			location,
			v.data());
		break;
	default:
		throw sge::exception(
			SGE_TEXT("vector size not right in glsl attribute variable!"));
	}

	return static_cast<result_type>(
		sge::ogl::glsl::attribute::type::int1 + v.size());
}

vector_visitor::result_type
vector_visitor::operator()(
	sge::math::vector::dynamic<
		double
	>::type const &v) const
{
	SGE_OPENGL_SENTRY

	switch(v.size()) {
	case 2:
		vertex_attrib_2dv(
			location,
			v.data());
		break;
	case 3:
		vertex_attrib_3dv(
			location,
			v.data());
		break;
	case 4:
		vertex_attrib_4dv(
			location,
			v.data());
		break;
	default:
		throw sge::exception(
			SGE_TEXT("vector size not right in glsl attribute variable!"));
	}

	return static_cast<result_type>(
		sge::ogl::glsl::attribute::type::float4 + v.size());
}

}
