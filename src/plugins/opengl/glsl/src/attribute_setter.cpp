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
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <cstddef>

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

void initialize_attribute_setter();

struct arithmetic_visitor
: boost::static_visitor<sge::ogl::glsl::attribute_type::type> {
	explicit arithmetic_visitor(
		GLint location);
		
	sge::ogl::glsl::attribute_type::type
	operator()(
		float) const;
	sge::ogl::glsl::attribute_type::type
	operator()(
		double) const;
private:
	GLint const location;
};

template<
	std::size_t Arity,
	typename FunFloat,
	typename FunDouble
>
struct vector_visitor 
: boost::static_visitor<sge::ogl::glsl::attribute_type::type> {
	vector_visitor(
		GLint location,
		FunFloat,
		FunDouble);
	
	sge::ogl::glsl::attribute_type::type
	operator()(
		sge::math::basic_vector<
			float,
			Arity
		> const &) const;
	sge::ogl::glsl::attribute_type::type
	operator()(
		sge::math::basic_vector<
			double,
			Arity
		> const &) const;
private:
	GLint const location;
	FunFloat const fun_float;
	FunDouble const fun_double;
};

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
	renderer::any_arithmetic const &f) const
{
	return boost::apply_visitor(
		arithmetic_visitor(
			location),
		f);
}

sge::ogl::glsl::attribute_type::type
sge::ogl::glsl::attribute_setter::operator()(
	renderer::any_vector2 const &v) const
{
	return boost::apply_visitor(
		vector_visitor<
			2,
			PFNGLVERTEXATTRIB2FVPROC,
			PFNGLVERTEXATTRIB2DVPROC
		>(
			location,
			vertex_attrib_2fv,
			vertex_attrib_2dv),
		v);
}

sge::ogl::glsl::attribute_type::type
sge::ogl::glsl::attribute_setter::operator()(
	renderer::any_vector3 const &v) const
{
	return boost::apply_visitor(
		vector_visitor<
			3,
			PFNGLVERTEXATTRIB3FVPROC,
			PFNGLVERTEXATTRIB3DVPROC
		>(
			location,
			vertex_attrib_3fv,
			vertex_attrib_3dv),
		v);
}

sge::ogl::glsl::attribute_type::type
sge::ogl::glsl::attribute_setter::operator()(
	renderer::any_vector4 const &v) const
{
	return boost::apply_visitor(
		vector_visitor<
			4,
			PFNGLVERTEXATTRIB4FVPROC,
			PFNGLVERTEXATTRIB4DVPROC
		>(
			location,
			vertex_attrib_4fv,
			vertex_attrib_4dv),
		v);
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

sge::ogl::glsl::attribute_type::type
arithmetic_visitor::operator()(
	float const f) const
{
	vertex_attrib_1f(location, f);
	return sge::ogl::glsl::attribute_type::float1;
}

sge::ogl::glsl::attribute_type::type
arithmetic_visitor::operator()(
	double const d) const
{
	vertex_attrib_1d(location, d);
	return sge::ogl::glsl::attribute_type::double1;
}


template<
	std::size_t Arity,
	typename FunFloat,
	typename FunDouble
>
vector_visitor<
	Arity,
	FunFloat,
	FunDouble
>::vector_visitor(
	GLint const location,
	FunFloat const fun_float,
	FunDouble const fun_double)
:
	location(location),
	fun_float(fun_float),
	fun_double(fun_double)
{}
	
template<
	std::size_t Arity,
	typename FunFloat,
	typename FunDouble
>
sge::ogl::glsl::attribute_type::type
vector_visitor<
	Arity,
	FunFloat,
	FunDouble
>::operator()(
	sge::math::basic_vector<
		float,
		Arity
	> const &v) const
{
	fun_float(location, v.data());
	return static_cast<sge::ogl::glsl::attribute_type::type>(
		sge::ogl::glsl::attribute_type::int1 + Arity);
}

template<
	std::size_t Arity,
	typename FunFloat,
	typename FunDouble
>
sge::ogl::glsl::attribute_type::type
vector_visitor<
	Arity,
	FunFloat,
	FunDouble
>::operator()(
	sge::math::basic_vector<
		double,
		Arity
	> const &v) const
{
	fun_double(location, v.data());
	return static_cast<sge::ogl::glsl::attribute_type::type>(
		sge::ogl::glsl::attribute_type::float4 + Arity);
}

}
