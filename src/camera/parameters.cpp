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


#include <sge/camera/parameters.hpp>
#include <sge/camera/identity_gizmo.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::camera::parameters::parameters(
	camera::movement_speed const &_movement_speed,
	camera::rotation_speed const &_rotation_speed,
	input::keyboard::device &_keyboard,
	input::mouse::device &_mouse)
:
	projection_(
		camera::projection::object()),
	movement_speed_(
		_movement_speed.get()),
	rotation_speed_(
		_rotation_speed.get()),
	gizmo_(
		camera::identity_gizmo()),
	keyboard_(
		_keyboard),
	mouse_(
		_mouse),
	active_(
		true)
{

}

sge::camera::parameters &
sge::camera::parameters::projection(
	projection::object const &_projection)
{
	projection_ =
		_projection;
	return
		*this;
}

sge::camera::parameters &
sge::camera::parameters::gizmo(
	camera::gizmo_type const &_gizmo)
{
	gizmo_ =
		_gizmo;
	return
		*this;
}

sge::camera::parameters &
sge::camera::parameters::active(
	bool const _active)
{
	active_ =
		_active;
	return
		*this;
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

sge::camera::gizmo_type const &
sge::camera::parameters::gizmo() const
{
	return gizmo_;
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

bool
sge::camera::parameters::active() const
{
	return active_;
}
