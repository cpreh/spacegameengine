//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/projection/orthogonal_xy.hpp>
#include <fcppt/math/matrix/row.hpp>


sge::renderer::matrix4
sge::renderer::projection::orthogonal_xy()
{
	sge::renderer::scalar const
		one(
			1.f
		),
		zero(
			0.f
		);

	return
		sge::renderer::matrix4(
			fcppt::math::matrix::row(
				one, zero, zero, zero
			),
			fcppt::math::matrix::row(
				zero, one, zero, zero
			),
			fcppt::math::matrix::row(
				zero, zero, zero, zero
			),
			fcppt::math::matrix::row(
				zero, zero, zero, one
			)
		);
}
