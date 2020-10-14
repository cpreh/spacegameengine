//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PARAMETER_VECTOR_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_VECTOR_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/vector/set.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/vector_decl.hpp>
#include <fcppt/math/size_type.hpp>


template<
	typename ValueType,
	fcppt::math::size_type N
>
sge::shader::parameter::vector<
	ValueType,
	N
>::vector(
	sge::cg::program::object_ref const _program,
	sge::shader::parameter::name const &_name,
	vector_type const &_initial_value
)
:
	parameter_(
		_program.get().parameter(
			_name.get()
		)
	)
{
	this->set(
		_initial_value
	);
}

template<
	typename ValueType,
	fcppt::math::size_type N
>
void
sge::shader::parameter::vector<
	ValueType,
	N
>::set(
	vector_type const &_vector
)
{
	sge::cg::parameter::vector::set(
		parameter_.object(),
		_vector
	);
}

template<
	typename ValueType,
	fcppt::math::size_type N
>
sge::shader::parameter::vector<
	ValueType,
	N
>::~vector<
	ValueType,
	N
>()
= default;

#endif
