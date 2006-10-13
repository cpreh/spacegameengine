/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GUI_EVENTS_HPP_INCLUDED
#define SGE_GUI_EVENTS_HPP_INCLUDED

#include "./types.hpp"
#include "../input/key_type.hpp"

namespace sge
{
namespace gui
{

class input_event {
public:
	input_event(const modifier_state& state)
		: state(state) {}
	bool shift_down() const { return state.shift_down; }
	bool ctrl_down() const { return state.ctrl_down; }
	bool alt_down() const { return state.alt_down; }
	const modifier_state& mod_state() const { return state; }
private:
	modifier_state state;
};

class mouse_move_event : public input_event {
public:
	mouse_move_event(const point p, const modifier_state& mod_state)
		: input_event(mod_state), p(p) {}
	point pos() const { return p; }
private:
	point p;
};

class mouse_button_event : public mouse_move_event {
public:
	mouse_button_event(const point pos, const key_code key, const modifier_state& mod_state, const bool v, const char c)
		: mouse_move_event(pos,mod_state), key(key), v(v), c(c) {}
	key_code code() const { return key; }
	bool value() const { return v; }
	char char_code() const { return c; }
private:
	key_code  key;
	bool      v;
	char      c;
};

class keyboard_button_event : public input_event {
public:
	keyboard_button_event(const key_code key, const modifier_state& mod_state, const bool v, const char c)
		: input_event(mod_state), key(key), v(v), c(c) {}
	key_code code() const { return key; }
	bool value() const { return v; }
	char char_code() const { return c; }
private:
	key_code key;
	bool     v;
	char     c;
};

class draw_event {
public:
	draw_event(const point p)
		: p(p) {}
	point pos() const { return p; }
private:
	point p;
};

}
}

#endif
