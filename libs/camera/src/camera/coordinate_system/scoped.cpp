//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/has_mutable_coordinate_system.hpp>
#include <sge/camera/coordinate_system/scoped.hpp>


sge::camera::coordinate_system::scoped::scoped(
	sge::camera::has_mutable_coordinate_system &_camera,
	sge::camera::coordinate_system::object const &_coordinate_system)
:
	camera_(
		_camera),
	old_coordinates_(
		_camera.coordinate_system())
{
	camera_.update_coordinate_system(
		_coordinate_system);
}

sge::camera::coordinate_system::scoped::~scoped()
{
	camera_.update_coordinate_system(
		old_coordinates_);
}
