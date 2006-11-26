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


#ifndef SGE_GUI_BUTTON_HPP_INCLUDED
#define SGE_GUI_BUTTON_HPP_INCLUDED

#include "../string.hpp"
#include "./rectangle.hpp"
#include "./types.hpp"

namespace sge
{
namespace gui
{

class manager;

class button : public rectangle {
public:
	button(manager& m, element* parent, const string& text, point pos, dim sz, color text_color = colors::white, bool visible = true, bool enabled = true);
	void text(const string& t) { _text = t; }
	const string& text() const { return _text; }
	void text_color(color c) { _text_color = c; }
	color text_color() const { return _text_color; }
private:
	string  _text;
	color   _text_color;
	virtual void on_draw(const draw_event& event);
};

typedef shared_ptr<button> button_ptr;

}
}

#endif
