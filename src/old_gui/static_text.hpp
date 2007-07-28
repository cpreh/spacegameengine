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


#ifndef SGE_GUI_STATIC_TEXT_HPP_INCLUDED
#define SGE_GUI_STATIC_TEXT_HPP_INCLUDED

#include "../renderer/font_types.hpp"
#include "../renderer/font.hpp"
#include "types.hpp"
#include "rectangle.hpp"

namespace sge
{
namespace gui
{

class manager;

class static_text : public rectangle {
public:
	static_text(manager& m, element* parent, const string& text, point pos, dim sz, color text_color = colors::white, bool visible = true, bool enabled = true);

	const string& text() const;
	void text(const string&);
	
	color text_color() const;
	void text_color(color);

	font_flag_t style() const;
	void style(font_flag_t);
private:
	string       _text;
	color        _text_color;
	unit         _line_height;
	font_flag_t _style;
	virtual void on_draw(const draw_event& event);
};

}
}

#endif
