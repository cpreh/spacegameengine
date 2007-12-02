/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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


#ifndef SGE_GUI_SCROLLBAR_HPP_INCLUDED
#define SGE_GUI_SCROLLBAR_HPP_INCLUDED

#include <boost/signal.hpp>

#include "iconbutton.hpp"
#include "widget.hpp"

namespace sge {
namespace gui {

class scrollbar : public widget {
public:
	scrollbar(widget *parent=0, skin::scroll_direction::type=skin::scroll_direction::vertical, std::string name="");

	inline step_type  large_step() const { return step.large; }
	inline void       large_step(step_type st) { step.large = st; }
	inline step_type  small_step() const { return step.small; }
	inline void       small_step(step_type st) { step.small = st; }
	inline value_type min() const { return step.min; }
	void              min(value_type);
	inline value_type max() const { return step.max; }
	void              max(value_type);

	inline value_type value() const { return val; }
	void              value(value_type);

	boost::signal<value_type> modified;
	boost::signal<value_type> modified_preview;

protected:
	skin::scroll_direction::type direction;
	struct { step_type  small, large; } step;
	struct { value_type min,   max;   } range;
	value_type val;

	struct drawer : public button {
		drawer(widget *parent, std::string name);
	protected:
		event_return_type on_mouse_move(const events::mouse_event &);
		void on_update();
	};

	drawer     draw;
	iconbutton upleft, downright;
	canvas     framebuffer;

	void perform_resize(dim2);
	void on_update();
};

}
}

#endif // SGE_GUI_SCROLLBAR_HPP_INCLUDED
