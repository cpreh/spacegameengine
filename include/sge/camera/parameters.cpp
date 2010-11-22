#include "parameters.hpp"

fruitcut::graphics::camera::parameters::parameters(
	projection::object const &_projection,
	scalar const _movement_speed,
	scalar const _rotation_speed,
	vec3 const &_position,
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

fruitcut::graphics::camera::projection::object const &
fruitcut::graphics::camera::parameters::projection() const
{
	return projection_;
}

fruitcut::scalar
fruitcut::graphics::camera::parameters::movement_speed() const
{
	return movement_speed_;
}

fruitcut::scalar
fruitcut::graphics::camera::parameters::rotation_speed() const
{
	return rotation_speed_;
}

fruitcut::vec3 const &
fruitcut::graphics::camera::parameters::position() const
{
	return position_;
}

sge::input::keyboard::device &
fruitcut::graphics::camera::parameters::keyboard() const
{
	return keyboard_;
}

sge::input::mouse::device &
fruitcut::graphics::camera::parameters::mouse() const
{
	return mouse_;
}
