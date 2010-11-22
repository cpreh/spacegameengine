#include <sge/camera/parameters.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::camera::parameters::parameters(
	projection::object const &_projection,
	renderer::scalar const _movement_speed,
	renderer::scalar const _rotation_speed,
	renderer::vector3 const &_position,
	sge::input::keyboard::device &_keyboard,
	sge::input::mouse::device &_mouse)
:
	projection_(
		_projection),
	movement_speed_(
		_movement_speed),
	rotation_speed_(
		_rotation_speed),
	position_(
		_position),
	keyboard_(
		_keyboard),
	mouse_(
		_mouse)
{
	
}

sge::camera::projection::object const &
sge::camera::parameters::projection() const
{
	return projection_;
}

sge::renderer::scalar
sge::camera::parameters::movement_speed() const
{
	return movement_speed_;
}

sge::renderer::scalar
sge::camera::parameters::rotation_speed() const
{
	return rotation_speed_;
}

sge::renderer::vector3 const &
sge::camera::parameters::position() const
{
	return position_;
}

sge::input::keyboard::device &
sge::camera::parameters::keyboard() const
{
	return keyboard_;
}

sge::input::mouse::device &
sge::camera::parameters::mouse() const
{
	return mouse_;
}
