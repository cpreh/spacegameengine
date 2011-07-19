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


#include <sge/renderer/glsl/to_ccv.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>

sge::renderer::matrix4 const
sge::renderer::glsl::to_ccv(
	sge::renderer::matrix4 const &_matrix
)
{
	sge::renderer::scalar const
		one(
			1.f
		),
		one_half(
			0.5f
		);

	return
		fcppt::math::matrix::translation(
			one,
			one,
			one_half
		)
		*
		fcppt::math::matrix::scaling(
			one,
			one,
			one_half
		)
		*
		_matrix;
}
