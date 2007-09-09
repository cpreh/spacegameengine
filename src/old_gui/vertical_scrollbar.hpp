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


#ifndef SGE_GUI_VERTICAL_SCROLLBAR_HPP_INCLUDED
#define SGE_GUI_VERTICAL_SCROLLBAR_HPP_INCLUDED

#include <cstddef>
#include "rectangle.hpp"
#include "scrollbar.hpp"

namespace sge
{
namespace gui
{

class manager;

class vertical_scrollbar : public rectangle {
public:
	typedef std::size_t size_type;
	vertical_scrollbar(manager& m, element* parent, point pos, dim sz, bool visible = true, bool enabled = true);
	void scroll_max(size_type max);
	size_type scroll_pos() const;
protected:
	void up_scroll_action();
	void down_scroll_action();
private:
	void on_glob_mouse_move(const mouse_move_event& event);
	void on_mouse_up(const mouse_button_event& event);
	void on_mouse_press(const mouse_button_event& event);
	void on_mouse_down(const mouse_button_event& event);
	void move_scrollbar(point click_pos);
	void recalc_pos();
	unit scroll_max_h() const;
	size_type s_pos,
	          s_max;
	inner_scrollbar scrollbar;
	scroll_button up_scroll_button,
	              down_scroll_button;
};

typedef shared_ptr<vertical_scrollbar> vertical_scrollbar_ptr;

}
}

#endif
