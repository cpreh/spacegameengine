//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PARAMETER_MATRIX_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_MATRIX_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/matrix/set.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/shader/parameter/matrix_decl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>


template<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
sge::shader::parameter::matrix<
	ValueType,
	M,
	N
>::matrix(
	sge::cg::program::object_ref const _program,
	sge::shader::parameter::name const &_name,
	sge::renderer::device::core const &_renderer,
	sge::shader::parameter::is_projection_matrix const &_is_projection_matrix,
	matrix_type const &_initial_value
)
:
	parameter_(
		_program.get().parameter(
			_name.get()
		)
	),
	is_projection_matrix_(
		_is_projection_matrix.get()
		&&
		_renderer.caps().normalized_cvv().get()
	)
{
	this->set(
		_initial_value
	);
}

template<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
void
sge::shader::parameter::matrix<
	ValueType,
	M,
	N
>::set(
	matrix_type const &_matrix
)
{
	sge::renderer::scalar const one{
		1.F
	};

	sge::renderer::scalar const two{
		0.5F
	};

	sge::renderer::scalar const zero{
		0.0F
	};

	sge::cg::parameter::matrix::set(
		parameter_.object(),
		is_projection_matrix_.get()
		?
			fcppt::math::matrix::translation(
				zero,
				zero,
				-one
			)
			*
			fcppt::math::matrix::scaling(
				one,
				one,
				two
			)
			*
			_matrix
		:
			_matrix
		);
}

namespace sge::shader::parameter
{
template<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
matrix<
	ValueType,
	M,
	N
>::~matrix()
= default;
}

#endif
