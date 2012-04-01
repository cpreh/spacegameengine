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


#include <sge/camera/spherical/parameters.hpp>
#include <limits>

sge::camera::spherical::parameters::parameters(
	input::keyboard::device &_keyboard,
	spherical::is_active const &_is_active,
	spherical::coordinate_system::object const &_coordinate_system,
	spherical::action::mapping const &_action_mapping)
:
	keyboard_(
		_keyboard),
	movement_speed_(
		spherical::coordinate_system::object(
			spherical::coordinate_system::azimuth(
				1.0f),
			spherical::coordinate_system::inclination(
				1.0f),
			spherical::coordinate_system::radius(
				1.0f))),
	is_active_(
		_is_active),
	coordinate_system_(
		_coordinate_system),
	action_mapping_(
		_action_mapping),
	origin_(
		sge::renderer::vector3::null()),
	minimum_radius_(
		0.0f),
	maximum_radius_(
		std::numeric_limits<sge::renderer::scalar>::infinity()),
	acceleration_factor_(
		spherical::coordinate_system::object(
			spherical::coordinate_system::azimuth(
				0.5f),
			spherical::coordinate_system::inclination(
				0.5f),
			spherical::coordinate_system::radius(
				0.5f))),
	damping_factor_(
		spherical::coordinate_system::object(
			spherical::coordinate_system::azimuth(
				0.90f),
			spherical::coordinate_system::inclination(
				0.90f),
			spherical::coordinate_system::radius(
				0.90f))),
	projection_matrix_()
{
}

sge::input::keyboard::device &
sge::camera::spherical::parameters::keyboard() const
{
	return
		keyboard_;
}

sge::camera::spherical::is_active const &
sge::camera::spherical::parameters::is_active() const
{
	return
		is_active_;
}

sge::camera::spherical::coordinate_system::object const &
sge::camera::spherical::parameters::coordinate_system() const
{
	return
		coordinate_system_;
}

sge::camera::spherical::action::mapping const &
sge::camera::spherical::parameters::action_mapping() const
{
	return
		action_mapping_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::movement_speed(
	spherical::movement_speed const &_movement_speed)
{
	movement_speed_ =
		_movement_speed;
	return
		*this;
}

sge::camera::spherical::movement_speed const &
sge::camera::spherical::parameters::movement_speed() const
{
	return
		movement_speed_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::origin(
	spherical::origin const &_origin)
{
	origin_ =
		_origin;
	return
		*this;
}

sge::camera::spherical::origin const &
sge::camera::spherical::parameters::origin() const
{
	return
		origin_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::minimum_radius(
	spherical::minimum_radius const &_minimum_radius)
{
	minimum_radius_ =
		_minimum_radius;
	return
		*this;
}

sge::camera::spherical::minimum_radius const &
sge::camera::spherical::parameters::minimum_radius() const
{
	return
		minimum_radius_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::maximum_radius(
	spherical::maximum_radius const &_maximum_radius)
{
	maximum_radius_ =
		_maximum_radius;
	return
		*this;
}

sge::camera::spherical::maximum_radius const &
sge::camera::spherical::parameters::maximum_radius() const
{
	return
		maximum_radius_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::acceleration_factor(
	spherical::acceleration_factor const &_acceleration_factor)
{
	acceleration_factor_ =
		_acceleration_factor;
	return
		*this;
}

sge::camera::spherical::acceleration_factor const &
sge::camera::spherical::parameters::acceleration_factor() const
{
	return
		acceleration_factor_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::damping_factor(
	spherical::damping_factor const &_damping_factor)
{
	damping_factor_ =
		_damping_factor;
	return
		*this;
}

sge::camera::spherical::damping_factor const &
sge::camera::spherical::parameters::damping_factor() const
{
	return
		damping_factor_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::projection(
	camera::projection_matrix const &_projection_matrix)
{
	projection_matrix_ =
		_projection_matrix;
	return
		*this;
}

sge::camera::optional_projection_matrix const &
sge::camera::spherical::parameters::projection_matrix() const
{
	return
		projection_matrix_;
}
