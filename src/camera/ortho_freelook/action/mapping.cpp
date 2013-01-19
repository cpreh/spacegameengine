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


#include <sge/camera/ortho_freelook/action/mapping.hpp>

sge::camera::ortho_freelook::action::mapping::mapping(
	action::zoom_in const &_zoom_in,
	action::zoom_out const &_zoom_out,
	action::activate_pan const &_activate_pan)
:
	zoom_in_(
		_zoom_in),
	zoom_out_(
		_zoom_out),
	activate_pan_(
		_activate_pan)
{
}

sge::camera::ortho_freelook::action::zoom_in const &
sge::camera::ortho_freelook::action::mapping::zoom_in() const
{
	return
		zoom_in_;
}

sge::camera::ortho_freelook::action::zoom_out const &
sge::camera::ortho_freelook::action::mapping::zoom_out() const
{
	return
		zoom_out_;
}

sge::camera::ortho_freelook::action::activate_pan const &
sge::camera::ortho_freelook::action::mapping::activate_pan() const
{
	return
		activate_pan_;
}
