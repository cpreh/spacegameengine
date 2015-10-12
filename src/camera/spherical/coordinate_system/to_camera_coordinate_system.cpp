/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/camera/spherical/coordinate_system/to_camera_coordinate_system.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/cross.hpp>
#include <fcppt/math/vector/hypersphere_to_cartesian.hpp>
#include <fcppt/math/vector/normalize.hpp>


namespace
{

sge::renderer::vector3
spherical_coordinates(
	sge::camera::spherical::coordinate_system::object const &_coordinate_system)
{
	sge::renderer::vector3 const hypersphere_coords(
		fcppt::math::vector::hypersphere_to_cartesian(
			sge::renderer::vector2(
				_coordinate_system.inclination().get(),
				_coordinate_system.azimuth().get())));

	return
		sge::renderer::vector3(
			hypersphere_coords.y(),
			hypersphere_coords.x(),
			hypersphere_coords.z());
}
}

sge::camera::coordinate_system::object
sge::camera::spherical::coordinate_system::to_camera_coordinate_system(
	spherical::coordinate_system::object const &_coordinate_system,
	spherical::origin const &_origin)
{
	sge::camera::coordinate_system::forward const forward_vector(
		spherical_coordinates(
			_coordinate_system));

	sge::camera::coordinate_system::position const position_vector(
		_origin.get() + _coordinate_system.radius().get() * forward_vector.get());

	sge::camera::coordinate_system::right const right_vector(
		fcppt::math::vector::normalize(
			fcppt::math::vector::cross(
				forward_vector.get(),
				sge::renderer::vector3(
					0.0f,
					1.0f,
					0.0f))));

	// No need to normalize here
	sge::camera::coordinate_system::up const up_vector(
		fcppt::math::vector::cross(
			right_vector.get(),
			forward_vector.get()));

	return
		sge::camera::coordinate_system::object(
			right_vector,
			up_vector,
			forward_vector,
			position_vector);
}
