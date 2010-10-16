/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gui/events/mouse_click.hpp>

sge::gui::events::mouse_click::mouse_click(
	point const &_pos,
	input::mouse::button_event const &_kp
)
:
	pos_(_pos),
	kp_(_kp)
{
}


sge::gui::point const &
sge::gui::events::mouse_click::pos() const
{
	return pos_;
}

sge::input::mouse::button_event const &
sge::gui::events::mouse_click::value() const
{
	return kp_;
}
