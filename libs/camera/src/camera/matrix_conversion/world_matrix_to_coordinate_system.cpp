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
