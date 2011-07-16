/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../projection.hpp"
//#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#if 0
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#endif

sge::renderer::matrix4 const
sge::opengl::convert::projection(
	renderer::matrix4 const &_matrix
)
{
	return _matrix;
#if 0
	renderer::scalar const
		m33(
			_matrix[2][2]
		),
		m34(
			_matrix[3][2]
		),
		near(
			-m34
			/ m33
		),
		far(
			m34 * near
			/
			(m34 + near)
		),
		zero(
			0.f
		),
		one(
			1.f
		);

	return
		fcppt::math::matrix::transpose(
			_matrix
		)
		*
		fcppt::math::matrix::translation(
			zero,
			zero,
			-far
		)
		*
		fcppt::math::matrix::scaling(
			one,
			one,
			static_cast<
				renderer::scalar
			>(
				-2.f
			)
		);
#endif
}
