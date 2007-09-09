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


#ifndef SGE_GUI_LIST_HPP_INCLUDED
#define SGE_GUI_LIST_HPP_INCLUDED

#include <cstddef>
#include <deque>
#include "rectangle.hpp"
#include "vertical_scrollbar.hpp"

namespace sge
{

class font;

namespace gui
{

class list : public rectangle {
public:
	typedef std::size_t     size_type;
	typedef std::ptrdiff_t  difference_type;
	static const difference_type no_selection = -1;

	list(manager& m, element* parent, point pos, dim sz, color text_color = colors::black, bool visible = true, bool enabled = true);
	void push_back(const string& str);
	void pop_back();
	void clear();
	void delete_element(size_type index);
	difference_type selected_index() const;
	const string& selected() const;
	string& selected();
	const string& operator[](size_type index) const;
	string& operator[](size_type index);
	size_type size() const;
private:
	virtual void on_draw(const draw_event& event);
	virtual void on_click(const mouse_button_event& event);
	void scroll_position_change(size_type npos);
	void calc_scrollbar();

	typedef std::deque<string> element_queue;
	font&                  my_font;
	color                  text_color;
	unit                   line_height;
	element_queue          elements;
	vertical_scrollbar     vscrollbar;
	difference_type        selected_;
};

typedef shared_ptr<list> list_ptr;

}
}

#endif
