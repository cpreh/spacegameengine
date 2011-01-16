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
#include <fcppt/variant/object_impl.hpp>

sge::camera::parameters::parameters(
	projection::object const &_projection,
	renderer::scalar const _movement_speed,
	renderer::scalar const _rotation_speed,
	gizmo_type const &_gizmo,
	sge::input::keyboard::device &_keyboard,
	sge::input::mouse::device &_mouse)
:
	projection_(
		_projection),
	movement_speed_(
		_movement_speed),
	rotation_speed_(
		_rotation_speed),
	gizmo_(
		_gizmo),
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
