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


#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/first_person/action/wasd_mapping.hpp>

sge::camera::first_person::parameters::parameters(
	sge::input::keyboard::device &_keyboard,
	sge::input::mouse::device &_mouse,
	first_person::is_active const &_is_active,
	first_person::movement_speed const &_movement_speed,
	camera::coordinate_system::object const &_coordinate_system)
:
	keyboard_(
		_keyboard),
	mouse_(
		_mouse),
	is_active_(
		_is_active),
	action_mapping_(
		action::wasd_mapping()),
	movement_speed_(
		_movement_speed),
	coordinate_system_(
		_coordinate_system),
	mouse_speed_multiplier_(
		1.0f),
	projection_matrix_()
{
}

sge::input::keyboard::device &
sge::camera::first_person::parameters::keyboard() const
{
	return
		keyboard_;
}

sge::input::mouse::device &
sge::camera::first_person::parameters::mouse() const
{
	return
		mouse_;
}

sge::camera::first_person::is_active const &
sge::camera::first_person::parameters::is_active() const
{
	return
		is_active_;
}

sge::camera::first_person::parameters &
sge::camera::first_person::parameters::action_mapping(
	action::mapping const &_action_mapping)
{
	action_mapping_ =
		_action_mapping;

	return
		*this;
}

sge::camera::first_person::action::mapping const &
sge::camera::first_person::parameters::action_mapping() const
{
	return
		action_mapping_;
}

sge::camera::first_person::movement_speed const &
sge::camera::first_person::parameters::movement_speed() const
{
	return movement_speed_;
}

sge::camera::coordinate_system::object const &
sge::camera::first_person::parameters::coordinate_system() const
{
	return coordinate_system_;
}

sge::camera::first_person::parameters &
sge::camera::first_person::parameters::mouse_speed_multiplier(
	camera::first_person::mouse_speed_multiplier const &_mouse_speed_multiplier)
{
	mouse_speed_multiplier_ =
		_mouse_speed_multiplier;

	return
		*this;
}

sge::camera::first_person::mouse_speed_multiplier const &
sge::camera::first_person::parameters::mouse_speed_multiplier() const
{
	return
		mouse_speed_multiplier_;
}

sge::camera::first_person::parameters &
sge::camera::first_person::parameters::projection(
	camera::projection_matrix const &_projection_matrix)
{
	projection_matrix_ =
		_projection_matrix;

	return
		*this;
}

sge::camera::optional_projection_matrix const &
sge::camera::first_person::parameters::projection_matrix() const
{
	return
		projection_matrix_;
}
