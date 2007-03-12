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


#ifndef SGE_GUI_TEXT_EDIT_HPP_INCLUDED
#define SGE_GUI_TEXT_EDIT_HPP_INCLUDED

#include "types.hpp"
#include "rectangle.hpp"
#include "text_cursor.hpp"
#include "../renderer/font_types.hpp"

namespace sge
{

class font;

namespace gui
{

class manager;

class text_edit : public rectangle {
public:
	text_edit(manager& m, element* parent, point pos, dim sz, const string& text = "", color text_color = colors::white, bool visible = true, bool enabled = true);
	const string& text() const;
	void text(const string& text);
	color text_color() const;
	void text_color(const color c);
private:
	virtual void on_key_press(const keyboard_button_event& event);
	virtual void on_click(const mouse_button_event& event);
	virtual void on_draw(const draw_event& event);
	void increase_cursor_pos();
	void decrease_cursor_pos();
	unit text_width() const;
	unit text_height() const;
	
	font&                  my_font;
	string                 _text;
	color                  _text_color;
	string::size_type      text_start,
	                       cursor_pos;
	text_cursor            cur;
	static const font_flag_t flags = FTF_AlignLeft | FTF_AlignVCenter | FTF_NoMultiLine;
};

typedef shared_ptr<text_edit> text_edit_ptr;

}
}

#endif
