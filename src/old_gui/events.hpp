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


#ifndef SGE_GUI_EVENTS_HPP_INCLUDED
#define SGE_GUI_EVENTS_HPP_INCLUDED

#include "types.hpp"
#include "../input/key_type.hpp"

namespace sge
{
namespace gui
{

class mouse_move_event {
public:
	mouse_move_event(const point p, const mod_state& _state)
	 : p(p),
	   _state(_state)
	{}

	point pos() const { return p; }
	const mod_state& state() const { return _state; }
private:
	point p;
	mod_state _state;
};

class mouse_button_event : public mouse_move_event {
public:
	mouse_button_event(const point pos, const key_code key, const mod_state& mod_state, const bool v, const key_type::char_type c)
		: mouse_move_event(pos,mod_state), key(key), v(v), c(c) {}
	key_code code() const { return key; }
	bool value() const { return v; }
	key_type::char_type char_code() const { return c; }
private:
	key_code  key;
	bool      v;
	uchar_t   c;
};

class keyboard_button_event {
public:
	keyboard_button_event(const key_code key, const mod_state& _state, const bool v, const key_type::char_type c)
	 : key(key),
	   v(v),
	   c(c),
	   _state(_state)
	{}
	key_code code() const { return key; }
	bool value() const { return v; }
	key_type::char_type char_code() const { return c; }
	const mod_state& state() const { return _state; }
private:
	key_code  key;
	bool      v;
	key_type::char_type   c;
	mod_state _state;
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
