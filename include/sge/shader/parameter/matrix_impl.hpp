#ifndef SGE_SHADER_PARAMETER_MATRIX_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_MATRIX_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/matrix/set.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/shader/parameter/matrix_decl.hpp>


template
<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
sge::shader::parameter::matrix<ValueType,M,N>::matrix(
	sge::cg::program::object &_program,
	sge::shader::parameter::name const &_name,
	sge::shader::parameter::is_projection_matrix const &_is_projection_matrix,
	matrix_type const &_initial_value)
:
	parameter_(
		_program.parameter(
			_name.get())),
	is_projection_matrix_(
		_is_projection_matrix)
{
	this->set(
		_initial_value);
}

template
<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
void
sge::shader::parameter::matrix<ValueType,M,N>::set(
	matrix_type const &_matrix)
{
	sge::cg::parameter::matrix::set(
		parameter_.object(),
		_matrix
		/*
		is_projection_matrix_.get()
		?

		:
		_matrix*/);
}

template
<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
sge::shader::parameter::matrix<ValueType,M,N>::~matrix()
{
}

#endif
