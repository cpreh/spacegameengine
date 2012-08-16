#include <sge/camera/coordinate_system/scoped.hpp>
#include <sge/camera/has_mutable_coordinate_system.hpp>

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
