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

#include "../shared_ptr.hpp"
#include "./types.hpp"
#include "./rectangle.hpp"

namespace sge
{
namespace gui
{

class manager;

class static_text : public rectangle {
public:
	static_text(manager& m, element* parent, const std::string& text, point pos, dim sz, color text_color = colors::black, bool visible = true, bool enabled = true);
	const std::string& text() const { return _text; }
	void text(const std::string& t) { _text = t; }
	color text_color() const { return _text_color; }
	void text_color(const color c) { _text_color = c; }
private:
	std::string _text;
	color _text_color;
	virtual void on_draw(const draw_event& event);
};

typedef shared_ptr<static_text> static_text_ptr;

}
}

#endif
