//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/coordinate_system/forward.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/coordinate_system/position.hpp>
#include <sge/camera/coordinate_system/right.hpp>
#include <sge/camera/coordinate_system/up.hpp>


sge::camera::coordinate_system::object::object(
	sge::camera::coordinate_system::right const _right,
	sge::camera::coordinate_system::up const _up,
	sge::camera::coordinate_system::forward const _forward,
	sge::camera::coordinate_system::position const _position
)
:
	right_(
		_right
	),
	up_(
		_up
	),
	forward_(
		_forward
	),
	position_(
		_position
	)
{
}

sge::camera::coordinate_system::right const &
sge::camera::coordinate_system::object::right() const
{
	return
		right_;
}

void
sge::camera::coordinate_system::object::right(
	sge::camera::coordinate_system::right const &_right
)
{
	right_ =
		_right;
}

sge::camera::coordinate_system::up const &
sge::camera::coordinate_system::object::up() const
{
	return
		up_;
}

void
sge::camera::coordinate_system::object::up(
	sge::camera::coordinate_system::up const &_up
)
{
	up_ =
		_up;
}

sge::camera::coordinate_system::forward const &
sge::camera::coordinate_system::object::forward() const
{
	return
		forward_;
}

void
sge::camera::coordinate_system::object::forward(
	sge::camera::coordinate_system::forward const &_forward
)
{
	forward_ =
		_forward;
}

sge::camera::coordinate_system::position const &
sge::camera::coordinate_system::object::position() const
{
	return
		position_;
}

void
sge::camera::coordinate_system::object::position(
	sge::camera::coordinate_system::position const &_position
)
{
	position_ =
		_position;
}
