//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/impl/projection/check_near_far.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/math/matrix/row.hpp>


sge::renderer::matrix4
sge::renderer::projection::orthogonal(
	sge::renderer::projection::rect const &_rect,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far
)
{
	sge::renderer::impl::projection::check_near_far(
		_near,
		_far
	);

	sge::renderer::scalar const
		one(
			1.f
		),
		zero(
			0.f
		),
		left(
			_rect.left()
		),
		right(
			_rect.right()
		),
		top(
			_rect.top()
		),
		bottom(
			_rect.bottom()
		),
		near(
			_near.get()
		),
		far(
			_far.get()
		);

	return
		sge::renderer::matrix4(
			fcppt::math::matrix::row(
				2.f / (right - left), zero, zero, (left + right) / (left - right)
			),
			fcppt::math::matrix::row(
				zero, 2.f / (top - bottom), zero, (top + bottom) / (bottom - top)
			),
			fcppt::math::matrix::row(
				zero, zero, 1.f / (far - near), near / (near - far)
			),
			fcppt::math::matrix::row(
				zero, zero, zero, one
			)
		);
}
