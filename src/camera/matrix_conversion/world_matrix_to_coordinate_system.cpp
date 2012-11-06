/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world_matrix_to_coordinate_system.hpp>
#include <fcppt/math/matrix/inverse.hpp>


sge::camera::coordinate_system::object
sge::camera::matrix_conversion::world_matrix_to_coordinate_system(
	sge::renderer::matrix4 const &_m)
{
	sge::renderer::matrix4 const inverted(
		fcppt::math::matrix::inverse(
			_m));

	return
		sge::camera::coordinate_system::object(
			sge::camera::coordinate_system::right(
				sge::renderer::vector3(
					_m[0][0],
					_m[0][1],
					_m[0][2])),
			sge::camera::coordinate_system::up(
				sge::renderer::vector3(
					_m[1][0],
					_m[1][1],
					_m[1][2])),
			sge::camera::coordinate_system::forward(
				sge::renderer::vector3(
					_m[2][0],
					_m[2][1],
					_m[2][2])),
			sge::camera::coordinate_system::position(
				sge::renderer::vector3(
					-inverted[0][3],
					-inverted[1][3],
					-inverted[2][3])));
}
