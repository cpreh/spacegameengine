/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/camera/ortho_freelook/action/wsg_mapping.hpp>

sge::camera::ortho_freelook::parameters::parameters(
	sge::input::mouse::device &_mouse,
	sge::input::keyboard::device &_keyboard,
	renderer::projection::near const &_near,
	renderer::projection::far const &_far,
	sge::camera::is_active const &_is_active)
:
	mouse_(
		_mouse),
	keyboard_(
		_keyboard),
	zoom_speed_(
		renderer::vector2(
			0.30f,
			0.30f)),
	pan_speed_(
		renderer::vector2(
			0.01f,
			0.01f)),
	projection_rectangle_(),
	near_(
		_near),
	far_(
		_far),
	is_active_(
		_is_active),
	action_mapping_(
		action::wsg_mapping())
{
}

sge::input::mouse::device &
sge::camera::ortho_freelook::parameters::mouse() const
{
	return mouse_;
}

sge::input::keyboard::device &
sge::camera::ortho_freelook::parameters::keyboard() const
{
	return keyboard_;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::zoom_speed(
	ortho_freelook::zoom_speed const &_zoom_speed)
{
	zoom_speed_ =
		_zoom_speed;
	return
		*this;
}

sge::camera::ortho_freelook::zoom_speed const &
sge::camera::ortho_freelook::parameters::zoom_speed() const
{
	return
		zoom_speed_;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::action_mapping(
	action::mapping const &_action_mapping)
{
	action_mapping_ =
		_action_mapping;
	return
		*this;
}

sge::camera::ortho_freelook::action::mapping const &
sge::camera::ortho_freelook::parameters::action_mapping() const
{
	return
		action_mapping_;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::pan_speed(
	ortho_freelook::pan_speed const &_pan_speed)
{
	pan_speed_ =
		_pan_speed;
	return
		*this;
}

sge::camera::ortho_freelook::pan_speed const &
sge::camera::ortho_freelook::parameters::pan_speed() const
{
	return
		pan_speed_;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::projection_rectangle(
	renderer::projection::rect const &_projection_rectangle)
{
	projection_rectangle_ =
		ortho_freelook::optional_projection_rectangle(
			_projection_rectangle);
	return
		*this;
}

sge::camera::ortho_freelook::optional_projection_rectangle const &
sge::camera::ortho_freelook::parameters::projection_rectangle() const
{
	return
		projection_rectangle_;
}

sge::renderer::projection::near const &
sge::camera::ortho_freelook::parameters::near() const
{
	return
		near_;
}

sge::renderer::projection::far const &
sge::camera::ortho_freelook::parameters::far() const
{
	return
		far_;
}

sge::camera::is_active const &
sge::camera::ortho_freelook::parameters::is_active() const
{
	return
		is_active_;
}

sge::camera::ortho_freelook::parameters::~parameters()
{
}
