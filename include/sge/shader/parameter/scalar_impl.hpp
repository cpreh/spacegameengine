#ifndef SGE_SHADER_PARAMETER_SCALAR_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_SCALAR_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/scalar/set.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/shader/parameter/scalar_decl.hpp>


template<typename ValueType>
sge::shader::parameter::scalar<ValueType>::scalar(
	sge::cg::program::object &_program,
	sge::shader::parameter::name const &_name,
	value_type const _initial_value)
:
	parameter_(
		_program.parameter(
			_name.get()))
{
	this->set(
		_initial_value);
}

template<typename ValueType>
void
sge::shader::parameter::scalar<ValueType>::set(
	value_type const _scalar)
{
	sge::cg::parameter::scalar::set(
		parameter_.object(),
		_scalar);
}

template<typename ValueType>
sge::shader::parameter::scalar<ValueType>::~scalar()
{
}

#endif
