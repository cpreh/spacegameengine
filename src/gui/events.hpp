/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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

#include <set>

#include "canvas.hpp"
#include "types.hpp"

namespace sge {
namespace gui {

class widget;

namespace events {

struct child_event {
	widget *child;
};

// TODO: drag_drop_event

struct focus_event {
	widget *losefocus,
	       *getfocus;
};

struct keyboard_event {
	typedef std::string keyname;
	keyname pressedkey;
	bool repeated;
	std::set<keyname> modifiers;
};

struct mouse_event {
	typedef unsigned button;
	enum buttons {
		NONE,
		LEFT,
		RIGHT,
		MIDDLE
	};
	button pressed;
	std::set<button> pressstate;
	point position;
	point oldposition;
	point globalposition;
	point oldglobalposition;
};

struct mouse_wheel_event : public mouse_event {
	enum direction_e {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	direction_e direction;
};

struct paint_event {
	canvas &dest;
	point   position;
};

struct parent_event {
	widget *parent;
};

}
}
}

#endif // SGE_GUI_EVENTS_HPP_INCLUDED
