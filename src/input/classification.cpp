/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/classification.hpp>

bool sge::input::is_mouse_button(
	key_code const key)
{
	return (key & kc::input_type_mask) == kc::input_type_mouse_key;
}

bool sge::input::is_mouse_axis(
	key_code const key)
{
	return (key & kc::input_type_mask) == kc::input_type_mouse_axis;
}

bool sge::input::is_keyboard_key(
	key_code const key)
{
	return (key & kc::input_type_mask) == kc::input_type_keyboard;
}

bool sge::input::is_shift(
	key_code const key)
{
	return
		(key == kc::key_lshift) ||
		(key == kc::key_rshift);
}

bool sge::input::is_ctrl(
	key_code const key)
{
	// TODO: reevaluate role of altgr
	return
		(key == kc::key_lctrl) ||
		(key == kc::key_rctrl) ||
		(key == kc::key_altgr);
}

bool sge::input::is_alt(
	key_code const key)
{
	// TODO: reevaluate role of altgr
	return
		(key == kc::key_alt  ) ||
		(key == kc::key_altgr);
}
