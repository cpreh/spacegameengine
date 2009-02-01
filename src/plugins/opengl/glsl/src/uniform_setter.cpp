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
#include <sge/math/matrix/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/dynamic.hpp>
#include <sge/array_wrapper_impl.hpp>
#include <sge/once.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/format.hpp>
#include <sge/assert.hpp>
#include <sge/raw_vector_impl.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/get.hpp>

namespace
{

PFNGLUNIFORM1IPROC uniform_1i;
PFNGLUNIFORM1IVPROC uniform_1iv;
PFNGLUNIFORM2IVPROC uniform_2iv;
PFNGLUNIFORM3IVPROC uniform_3iv;
PFNGLUNIFORM4IVPROC uniform_4iv;
PFNGLUNIFORM1FPROC uniform_1f;
PFNGLUNIFORM1FVPROC uniform_1fv;
PFNGLUNIFORM2FVPROC uniform_2fv;
PFNGLUNIFORM3FVPROC uniform_3fv;
PFNGLUNIFORM3FVPROC uniform_4fv;
PFNGLUNIFORMMATRIX2FVPROC uniform_matrix_2fv;
PFNGLUNIFORMMATRIX3FVPROC uniform_matrix_3fv;
PFNGLUNIFORMMATRIX4FVPROC uniform_matrix_4fv;
PFNGLUNIFORMMATRIX2X3FVPROC uniform_matrix_2x3fv;
PFNGLUNIFORMMATRIX3X2FVPROC uniform_matrix_3x2fv;
PFNGLUNIFORMMATRIX2X4FVPROC uniform_matrix_2x4fv;
PFNGLUNIFORMMATRIX4X2FVPROC uniform_matrix_4x2fv;
PFNGLUNIFORMMATRIX3X4FVPROC uniform_matrix_3x4fv;
PFNGLUNIFORMMATRIX4X3FVPROC uniform_matrix_4x3fv;

void initialize_uniform_setter();

template<
	typename Dest,
	typename T
>
sge::raw_vector<Dest> const
convert_array(
	sge::array_wrapper<T> const &);

struct vector_visitor
: boost::static_visitor<sge::ogl::glsl::uniform_type> {

	explicit vector_visitor(
		GLint location);
	
	template<
		typename T,
		typename N,
		typename S
	>
	sge::ogl::glsl::uniform_type const
	operator()(
		sge::math::vector::basic<
			T,
			N,
			S
		> const &) const;
private:
	GLint const location;
};

struct vector_array_visitor
: boost::static_visitor<sge::ogl::glsl::uniform_type> {

	typedef sge::array_wrapper<
		sge::renderer::glsl::uniform_vector
	> array_type;

	vector_array_visitor(
		GLint location,
		array_type const &);
	
	template<
		typename T,
		typename N,
		typename S
	>
	sge::ogl::glsl::uniform_type const
	operator()(
		sge::math::vector::basic<
			T,
			N,
			S
		> const &) const;
private:
	GLint const location;
	array_type const &arr;
};

sge::ogl::glsl::uniform_type const
set_vector(
	GLint location,
	GLfloat const *data,
	GLsizei size,
	GLsizei elements);

sge::ogl::glsl::uniform_type const
set_vector(
	GLint location,
	GLint const *data,
	GLsizei size,
	GLsizei elements);

sge::ogl::glsl::uniform_type const
set_matrix(
	GLint location,
	GLfloat const *data,
	GLsizei rows,
	GLsizei columns,
	GLsizei elements);

}

sge::ogl::glsl::uniform_setter::uniform_setter(
	GLint const location)
:
	location(location)
{
	initialize_uniform_setter();
}
	
sge::ogl::glsl::uniform_type const
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::int_type const i) const
{
	uniform_1i(
		location,
		i);
	
	return uniform_type(
		uniform_element_type::int1,
		1);
}
	
sge::ogl::glsl::uniform_type const
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::float_type const &f) const
{
	uniform_1f(
		location,
		f);
	
	return uniform_type(
		uniform_element_type::float1,
		1);
}

sge::ogl::glsl::uniform_type const
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::uniform_vector const &v) const
{
	return boost::apply_visitor(
		vector_visitor(
			location),
		v);
}

sge::ogl::glsl::uniform_type const
sge::ogl::glsl::uniform_setter::operator()(
	renderer::glsl::uniform_matrix const &m) const
{
	return set_matrix(
		location,
		m.data(),
		m.rows(),
		m.columns(),
		1);
}

sge::ogl::glsl::uniform_type const
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::int_type> const &m) const
{
	uniform_1iv(
		location,
		static_cast<GLsizei>(m.size()),
		m.data());

	return uniform_type(
		uniform_element_type::int1,
		static_cast<
			uniform_type::size_type
		>(
			m.size()));
}

sge::ogl::glsl::uniform_type const
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::float_type> const &m) const
{
	uniform_1fv(
		location,
		static_cast<GLsizei>(m.size()),
		m.data());

	return uniform_type(
		uniform_element_type::float1,
		static_cast<
			uniform_type::size_type
		>(
			m.size()));
}

sge::ogl::glsl::uniform_type const
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::uniform_vector> const &a) const
{
	SGE_ASSERT(!a.empty());

	return boost::apply_visitor(
		vector_array_visitor(
			location,
			a),
		*a.begin());
}

sge::ogl::glsl::uniform_type const
sge::ogl::glsl::uniform_setter::operator()(
	array_wrapper<renderer::glsl::uniform_matrix> const &a) const
{
	// TODO: sanity check all the elements
	SGE_ASSERT(!a.empty());	

	return set_matrix(
		location,
		convert_array<
			GLfloat
		>(a).data(),
		a.begin()->rows(),
		a.begin()->columns(),
		static_cast<
			GLsizei
		>(
			a.size()));
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
		uniform_2iv = glUniform2iv;
		uniform_3iv = glUniform3iv;
		uniform_4iv = glUniform4iv;
		uniform_1f = glUniform1f;
		uniform_1fv = glUniform1fv;
		uniform_2fv = glUniform2fv;
		uniform_3fv = glUniform3fv;
		uniform_4fv = glUniform4fv;
		uniform_matrix_2fv = glUniformMatrix2fv;
		uniform_matrix_3fv = glUniformMatrix3fv;
		uniform_matrix_4fv = glUniformMatrix4fv;
		uniform_matrix_2x3fv = glUniformMatrix2x3fv;
		uniform_matrix_3x2fv = glUniformMatrix3x2fv;
		uniform_matrix_2x4fv = glUniformMatrix2x4fv;
		uniform_matrix_4x2fv = glUniformMatrix4x2fv;
		uniform_matrix_3x4fv = glUniformMatrix3x4fv;
		uniform_matrix_4x3fv = glUniformMatrix4x3fv;
	}
	else
	{
		uniform_1i = glUniform1iARB;
		uniform_1iv = glUniform1ivARB;
		uniform_2iv = glUniform2ivARB;
		uniform_3iv = glUniform3ivARB;
		uniform_4iv = glUniform4ivARB;
		uniform_1f = glUniform1fARB;
		uniform_1fv = glUniform1fvARB;
		uniform_2fv = glUniform2fvARB;
		uniform_3fv = glUniform3fvARB;
		uniform_4fv = glUniform4fvARB;
		uniform_matrix_2fv = glUniformMatrix2fvARB;
		uniform_matrix_3fv = glUniformMatrix3fvARB;
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

vector_visitor::vector_visitor(
	GLint const location)
:
	location(location)
{}
	
template<
	typename T,
	typename N,
	typename S
>
sge::ogl::glsl::uniform_type const
vector_visitor::operator()(
	sge::math::vector::basic<
		T,
		N,
		S
	> const &v) const
{
	return set_vector(
		location,
		v.data(),
		v.size(),
		1);
}


vector_array_visitor::vector_array_visitor(
	GLint const location,
	array_type const &arr)
:
	location(location),
	arr(arr)
{}
	
template<
	typename T,
	typename N,
	typename S
>
sge::ogl::glsl::uniform_type const
vector_array_visitor::operator()(
	sge::math::vector::basic<
		T,
		N,
		S
	> const &v) const
{
	sge::raw_vector<
		T
	> narray;

	for(array_type::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		typedef sge::math::vector::basic<
			T,
			N,
			S
		> vec_type;

		vec_type const v(
			boost::get<
				vec_type
			>(
				*it));

		narray.insert(narray.end(), v.begin(), v.end());
	}

	return set_vector(
		location,
		narray.data(),
		v.size(),
		arr.size());
}

sge::ogl::glsl::uniform_type const
set_vector(
	GLint const location,
	GLfloat const *const data,
	GLsizei const size,
	GLsizei const elements)
{
	namespace et = sge::ogl::glsl::uniform_element_type;

	switch(size) {
	case 2:
		uniform_2fv(
			location,
			elements,
			data);

		return sge::ogl::glsl::uniform_type(
			et::float2,
			elements);
	case 3:
		uniform_3fv(
			location,
			elements,
			data);

		return sge::ogl::glsl::uniform_type(
			et::float3,
			elements);
	case 4:
		uniform_4fv(
			location,
			elements,
			data);

		return sge::ogl::glsl::uniform_type(
			et::float4,
			elements);
	default:
		throw sge::exception(
			(sge::format(
				SGE_TEXT("Invalid vector dimension in glsl: %1%"))
			% size).str());
	}
}

sge::ogl::glsl::uniform_type const
set_vector(
	GLint const location,
	GLint const *const data,
	GLsizei const size,
	GLsizei const elements)
{
	namespace et = sge::ogl::glsl::uniform_element_type;

	switch(size) {
	case 2:
		uniform_2iv(
			location,
			elements,
			data);

		return sge::ogl::glsl::uniform_type(
			et::int2,
			elements);
	case 3:
		uniform_3iv(
			location,
			elements,
			data);

		return sge::ogl::glsl::uniform_type(
			et::int3,
			elements);
	case 4:
		uniform_4iv(
			location,
			elements,
			data);

		return sge::ogl::glsl::uniform_type(
			et::int4,
			elements);
	default:
		throw sge::exception(
			(sge::format(
				SGE_TEXT("Invalid vector dimension in glsl: %1%"))
			% size).str());
	}
}

sge::ogl::glsl::uniform_type const
set_matrix(
	GLint const location,
	GLfloat const *const data,
	GLsizei const rows,
	GLsizei const columns,
	GLsizei const elements)
{
	if(
		!sge::ogl::glsl::is_native()
		&& rows != columns
	)
		throw sge::exception(
			(sge::format(
				SGE_TEXT("You specified a glsl matrix whose dimensions are not equal which is not supported by the ARB extension!")
				SGE_TEXT(" Specified size was: %1%x%2%"))
			% columns
			% rows).str());

	namespace et = sge::ogl::glsl::uniform_element_type;

	switch(rows) {
	case 2:
		switch(columns) {
		case 2:
			uniform_matrix_2fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix2x2,
				elements);
		case 3:
			uniform_matrix_3x2fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix3x2,
				elements);
		case 4:
			uniform_matrix_4x2fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix4x2,
				elements);
		}
		break;
	case 3:
		switch(columns) {
		case 2:
			uniform_matrix_3x2fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix3x2,
				elements);
		case 3:
			uniform_matrix_3fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix3x3,
				elements);
		case 4:
			uniform_matrix_4x3fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix4x3,
				elements);
		}
		break;
	case 4:
		switch(columns) {
		case 2:
			uniform_matrix_4x2fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix4x2,
				elements);
		case 3:
			uniform_matrix_3x4fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix3x4,
				elements);
		case 4:
			uniform_matrix_4fv(
				location,
				elements,
				false,
				data);

			return sge::ogl::glsl::uniform_type(
				et::matrix4x4,
				elements);
		}
		break;
	}

	throw sge::exception(
		(sge::format(
			SGE_TEXT("Invalid matrix dimensions in glsl: %1%x%2%"))
			% columns
			% rows).str());
}

}
