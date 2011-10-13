/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <fcppt/variant/object_impl.hpp>
#include <sge/camera/gizmo_type.hpp>
#include <sge/camera/identity_gizmo.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/spherical/parameters.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/renderer/scalar.hpp>

sge::camera::spherical::parameters::parameters(
	spherical::movement_speed const &_movement_speed,
	renderer::scalar const _min_radius,
	input::keyboard::device &_keyboard)
:
	projection_(
		camera::projection::object()),
	movement_speed_(
		_movement_speed.get()),
	min_radius_(
		_min_radius),
	acceleration_factor_(
		0.1f),
	damping_(
		0.95f),
	radius_(
		1.f),
	gizmo_(
		camera::identity_gizmo()),
	keyboard_(
		_keyboard),
	active_(
		true)
{
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::projection(
	projection::object const &_projection)
{
	projection_ =
		_projection;
	return
		*this;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::gizmo(
	camera::gizmo_type const &_gizmo)
{
	gizmo_ =
		_gizmo;
	return
		*this;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::active(
	bool const _active)
{
	active_ =
		_active;
	return
		*this;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::radius(
	sge::renderer::scalar const _radius)
{
	radius_ =
		_radius;
	return
		*this;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::acceleration_factor(
	sge::renderer::scalar const _acceleration_factor)
{
	acceleration_factor_ =
		_acceleration_factor;
	return
		*this;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::damping(
	sge::renderer::scalar const _damping)
{
	damping_ =
		_damping;
	return
		*this;
}

sge::camera::projection::object const &
sge::camera::spherical::parameters::projection() const
{
	return projection_;
}

sge::renderer::scalar
sge::camera::spherical::parameters::movement_speed() const
{
	return movement_speed_;
}

sge::renderer::scalar
sge::camera::spherical::parameters::min_radius() const
{
	return min_radius_;
}

sge::renderer::scalar
sge::camera::spherical::parameters::radius() const
{
	return radius_;
}

sge::renderer::scalar
sge::camera::spherical::parameters::acceleration_factor() const
{
	return acceleration_factor_;
}

sge::renderer::scalar
sge::camera::spherical::parameters::damping() const
{
	return damping_;
}

sge::camera::gizmo_type const &
sge::camera::spherical::parameters::gizmo() const
{
	return gizmo_;
}

sge::input::keyboard::device &
sge::camera::spherical::parameters::keyboard() const
{
	return keyboard_;
}

bool
sge::camera::spherical::parameters::active() const
{
	return active_;
}
