//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/coordinate_system/forward.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/coordinate_system/position.hpp>
#include <sge/camera/coordinate_system/right.hpp>
#include <sge/camera/coordinate_system/up.hpp>
#include <sge/camera/matrix_conversion/world_matrix_to_coordinate_system.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/matrix/at_r.hpp>
#include <fcppt/math/matrix/at_r_c.hpp>
#include <fcppt/math/matrix/inverse.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>


sge::camera::coordinate_system::object
sge::camera::matrix_conversion::world_matrix_to_coordinate_system(
	sge::renderer::matrix4 const &_m
)
{
	sge::renderer::matrix4 const inverted(
		fcppt::math::matrix::inverse(
			_m
		)
	);

	return
		sge::camera::coordinate_system::object(
			sge::camera::coordinate_system::right(
				fcppt::math::vector::narrow_cast<
					sge::renderer::vector3
				>(
					fcppt::math::matrix::at_r<
						0
					>(
						_m
					)
				)
			),
			sge::camera::coordinate_system::up(
				fcppt::math::vector::narrow_cast<
					sge::renderer::vector3
				>(
					fcppt::math::matrix::at_r<
						1
					>(
						_m
					)
				)
			),
			sge::camera::coordinate_system::forward(
				fcppt::math::vector::narrow_cast<
					sge::renderer::vector3
				>(
					fcppt::math::matrix::at_r<
						2
					>(
						_m
					)
				)
			),
			sge::camera::coordinate_system::position(
				sge::renderer::vector3(
					-fcppt::math::matrix::at_r_c<
						0,
						3
					>(
						inverted
					),
					-fcppt::math::matrix::at_r_c<
						1,
						3
					>(
						inverted
					),
					-fcppt::math::matrix::at_r_c<
						2,
						3
					>(
						inverted
					)
				)
			)
		);
}
