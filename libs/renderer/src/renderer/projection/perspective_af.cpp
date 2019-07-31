//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/impl/projection/check_near.hpp>
#include <sge/renderer/impl/projection/check_near_far.hpp>
#include <sge/renderer/projection/aspect.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/perspective_af.hpp>
#include <fcppt/math/matrix/row.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sge::renderer::matrix4
sge::renderer::projection::perspective_af(
	sge::renderer::projection::aspect const _aspect,
	sge::renderer::projection::fov const _fov,
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
		scale_y(
			1.f
			/
			std::tan(
				_fov.get()
				/
				2.f
			)
		),
		scale_x(
			scale_y
			/
			_aspect.get()
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
				scale_x, zero, zero, zero
			),
			fcppt::math::matrix::row(
				zero, scale_y, zero, zero
			),
			fcppt::math::matrix::row(
				zero, zero, far / (far - near), -near * far / (far - near)
			),
			fcppt::math::matrix::row(
				zero, zero, one, zero
			)
		);
}
