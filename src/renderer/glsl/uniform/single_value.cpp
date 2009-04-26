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



#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/dynamic_impl.hpp>
#include <sge/math/matrix/basic_impl.hpp>
#include <sge/math/matrix/dynamic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/size_type.hpp>
#include <sge/format.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>

namespace
{

class visitor : public boost::static_visitor<> {
public:
	explicit visitor(
		sge::renderer::glsl::uniform::variable_ptr);
	
	void
	operator()(
		sge::renderer::glsl::int_type) const;
	void
	operator()(
		sge::renderer::glsl::float_type) const;

	void
	operator()(
		sge::renderer::glsl::uniform::vector const &) const;

	void
	operator()(
		sge::renderer::glsl::uniform::matrix const &) const;
private:
	sge::renderer::glsl::uniform::variable_ptr const var;
};

class vector_visitor : public boost::static_visitor<> {
public:
	explicit vector_visitor(
		sge::renderer::glsl::uniform::variable_ptr);
		
	template<
		typename N,
		typename S
	>
	void
	operator()(
		sge::math::vector::basic<
			sge::renderer::glsl::int_type,
			N,
			S
		> const &) const;

	template<
		typename N,
		typename S
	>
	void
	operator()(
		sge::math::vector::basic<
			sge::renderer::glsl::float_type,
			N,
			S
		> const &) const;
private:
	sge::renderer::glsl::uniform::variable_ptr const var;
};

sge::renderer::glsl::uniform::float_value_type::type
convert_matrix_type(
	sge::renderer::glsl::uniform::matrix::dim_type const &);

sge::renderer::glsl::uniform::int_value_type::type
convert_int_vector_type(
	sge::math::size_type);

sge::renderer::glsl::uniform::float_value_type::type
convert_float_vector_type(
	sge::math::size_type);

}

void
sge::renderer::glsl::uniform::single_value(
	variable_ptr const var,
	single_value_type const &val)
{
	boost::apply_visitor(
		visitor(
			var),
		val);
}

namespace
{

visitor::visitor(
	sge::renderer::glsl::uniform::variable_ptr const var)
:
	var(var)
{}
	
void
visitor::operator()(
	sge::renderer::glsl::int_type const i) const
{
	var->set(
		sge::renderer::glsl::uniform::int_value(
			&i,
			1,
			sge::renderer::glsl::uniform::int_value_type::int1));
}

void
visitor::operator()(
	sge::renderer::glsl::float_type const f) const
{
	var->set(
		sge::renderer::glsl::uniform::float_value(
			&f,
			1,
			sge::renderer::glsl::uniform::float_value_type::float1));

}

void
visitor::operator()(
	sge::renderer::glsl::uniform::vector const &v) const
{
	boost::apply_visitor(
		vector_visitor(
			var),
		v);
}

void
visitor::operator()(
	sge::renderer::glsl::uniform::matrix const &m) const
{
	var->set(
		sge::renderer::glsl::uniform::float_value(
			m.data(),
			1,
			convert_matrix_type(
				m.dim())));
}


vector_visitor::vector_visitor(
	sge::renderer::glsl::uniform::variable_ptr const var)
:
	var(var)
{}
		
template<
	typename N,
	typename S
>
void
vector_visitor::operator()(
	sge::math::vector::basic<
		sge::renderer::glsl::int_type,
		N,
		S
	> const &v) const
{
	var->set(
		sge::renderer::glsl::uniform::int_value(
			v.data(),
			1,
			convert_int_vector_type(
				v.size())));
}

template<
	typename N,
	typename S
>
void
vector_visitor::operator()(
	sge::math::vector::basic<
		sge::renderer::glsl::float_type,
		N,
		S
	> const &v) const
{
	var->set(
		sge::renderer::glsl::uniform::float_value(
			v.data(),
			1,
			convert_float_vector_type(
				v.size())));
}

sge::renderer::glsl::uniform::float_value_type::type
convert_matrix_type(
	sge::renderer::glsl::uniform::matrix::dim_type const &d)
{
	namespace fv = sge::renderer::glsl::uniform::float_value_type;

	switch(d.w()) {
	case 2:
		switch(d.h()) {
		case 2:
			return fv::matrix2x2;
		case 3:
			return fv::matrix2x3;
		case 4:
			return fv::matrix2x4;
		}
		break;
	case 3:
		switch(d.h()) {
		case 2:
			return fv::matrix3x2;
		case 3:
			return fv::matrix3x3;
		case 4:
			return fv::matrix3x4;
		}
		break;
	case 4:
		switch(d.h()) {
		case 2:
			return fv::matrix4x2;
		case 3:
			return fv::matrix4x3;
		case 4:
			return fv::matrix2x4;
		}
		break;
	}

	throw sge::exception(
		(sge::format(
			SGE_TEXT("Invalid matrix dim in glsl::uniform::single_value: %1%"))
		% d).str());
}

sge::renderer::glsl::uniform::int_value_type::type
convert_int_vector_type(
	sge::math::size_type const sz)
{
	namespace iv = sge::renderer::glsl::uniform::int_value_type;

	switch(sz) {
	case 1:
		return iv::int1;
	case 2:
		return iv::int2;
	case 3:
		return iv::int3;
	case 4:
		return iv::int4;
	default:
		throw sge::exception(
			(sge::format(
				SGE_TEXT("Invalid vector dim in glsl::uniform::single_value: %1%"))
			% sz).str());
	}
}

sge::renderer::glsl::uniform::float_value_type::type
convert_float_vector_type(
	sge::math::size_type const sz)
{
	namespace fv = sge::renderer::glsl::uniform::float_value_type;

	switch(sz) {
	case 1:
		return fv::float1;
	case 2:
		return fv::float2;
	case 3:
		return fv::float3;
	case 4:
		return fv::float4;
	default:
		throw sge::exception(
			(sge::format(
				SGE_TEXT("Invalid vector dim in glsl::uniform::single_value: %1%"))
			% sz).str());
	}
}

}
