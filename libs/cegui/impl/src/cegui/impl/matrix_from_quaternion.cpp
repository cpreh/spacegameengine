//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/impl/matrix_from_quaternion.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/math/matrix/row.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Quaternion.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::matrix4
sge::cegui::impl::matrix_from_quaternion(
	CEGUI::Quaternion const &_quat
)
{
	sge::renderer::scalar const s = _quat.d_w;
	sge::renderer::scalar const x = _quat.d_x;
	sge::renderer::scalar const y = _quat.d_y;
	sge::renderer::scalar const z = _quat.d_z;

	return
		sge::renderer::matrix4(
			fcppt::math::matrix::row(
				1-2*(y*y + z*z), 2*x*y-2*s*z, 2*s*y + 2*x*z, 0.F
			),
			fcppt::math::matrix::row(
				2*x*y+2*s*z, 1-2*(x*x + z*z),-2*s*x+2*y*z,0.F
			),
			fcppt::math::matrix::row(
				-2*s*y + 2*x*z,2*s*x+2*y*z,1-2*(x*x+y*y),0.F
			),
			fcppt::math::matrix::row(
				0.F,0.F,0.F,1.F
			)
		);
}
