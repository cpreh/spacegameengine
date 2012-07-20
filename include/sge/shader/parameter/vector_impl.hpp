#ifndef SGE_SHADER_PARAMETER_VECTOR_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_VECTOR_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/vector/set.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/shader/parameter/vector_decl.hpp>


template
<
	typename ValueType,
	fcppt::math::size_type N
>
sge::shader::parameter::vector<ValueType,N>::vector(
	sge::cg::program::object &_program,
	sge::shader::parameter::name const &_name,
	vector_type const &_initial_value)
:
	parameter_(
		_program.parameter(
			_name.get()))
{
	this->set(
		_initial_value);
}

template
<
	typename ValueType,
	fcppt::math::size_type N
>
void
sge::shader::parameter::vector<ValueType,N>::set(
	vector_type const &_vector)
{
	sge::cg::parameter::vector::set(
		parameter_.object(),
		_vector);
}

template
<
	typename ValueType,
	fcppt::math::size_type N
>
sge::shader::parameter::vector<ValueType,N>::~vector()
{
}

#endif
