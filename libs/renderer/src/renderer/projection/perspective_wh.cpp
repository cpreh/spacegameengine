//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/impl/projection/check_near.hpp>
#include <sge/renderer/impl/projection/check_near_far.hpp>
#include <sge/renderer/projection/dim.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/perspective_wh.hpp>
#include <fcppt/math/matrix/row.hpp>


sge::renderer::matrix4
sge::renderer::projection::perspective_wh(
	sge::renderer::projection::dim const &_dim,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far
)
{
	sge::renderer::impl::projection::check_near_far(
		_near,
		_far
	);

	sge::renderer::impl::projection::check_near(
		_near
	);

	sge::renderer::scalar const
		far(
			_far.get()
		),
		near(
			_near.get()
		),
		h(
			_dim.h()
		),
		w(
			_dim.w()
		),
		zero(
			0.f
		),
		one(
			1.f
		);

	return
		sge::renderer::matrix4(
			fcppt::math::matrix::row(
				2 * near / w, zero, zero, zero
			),
			fcppt::math::matrix::row(
				zero, 2 * near / h, zero, zero
			),
			fcppt::math::matrix::row(
				zero, zero, far / (far - near), near * far / (near - far)
			),
			fcppt::math::matrix::row(
				zero, zero, one, zero
			)
		);
}
