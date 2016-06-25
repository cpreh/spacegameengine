/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SHADER_PARAMETER_MATRIX_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_MATRIX_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/matrix/set.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/shader/parameter/matrix_decl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>


template
<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
sge::shader::parameter::matrix<ValueType,M,N>::matrix(
	sge::cg::program::object &_program,
	sge::shader::parameter::name const &_name,
	sge::renderer::device::core const &_renderer,
	sge::shader::parameter::is_projection_matrix const &_is_projection_matrix,
	matrix_type const &_initial_value)
:
	parameter_(
		_program.parameter(
			_name.get())),
	is_projection_matrix_(
		_is_projection_matrix.get() && _renderer.caps().normalized_cvv().get()
		?
			true
		:
			false)
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
	sge::renderer::scalar const
		one(
			1.f),
		two(
			0.5f),
		zero(
			0.0f);

	sge::cg::parameter::matrix::set(
		parameter_.object(),
		is_projection_matrix_.get()
		?
			fcppt::math::matrix::translation(
				zero,
				zero,
				-one)
			*
			fcppt::math::matrix::scaling(
				one,
				one,
				two)
			*
			_matrix
		:
			_matrix);
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
