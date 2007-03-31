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


#ifndef SGE_GUI_SCROLLBAR_HPP_INCLUDED
#define SGE_GUI_SCROLLBAR_HPP_INCLUDED

#include "rectangle.hpp"
#include <boost/function.hpp>

namespace sge
{
namespace gui
{

class manager;

class inner_scrollbar : public rectangle {
public:
	inner_scrollbar(manager& m, element* parent, point pos, dim sz);
};

class scroll_button : public rectangle {
public:
	enum style { up_scroll, down_scroll };
	typedef boost::function<void()> action_function;
	scroll_button(manager& m, element* parent, point pos, dim sz, style s, action_function action);
private:
	virtual void on_mouse_press(const mouse_button_event& event);
	virtual void on_click(const mouse_button_event& event);
	virtual void on_draw(const draw_event& event);
	action_function action;
};

}
}

#endif
