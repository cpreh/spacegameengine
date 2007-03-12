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


#ifndef SGE_GUI_CHECK_BOX_HPP_INCLUDED
#define SGE_GUI_CHECK_BOX_HPP_INCLUDED

#include "types.hpp"
#include "rectangle.hpp"
#include "click_box.hpp"

namespace sge
{
namespace gui
{

class manager;

class check_box : public rectangle {
public:
	check_box(manager& man, element* parent, const string& text, point pos, dim size, color text_color = colors::white, bool value = false, bool visible = true, bool enabled = true);
	bool value() const;
	void text(const string& t);
	const string& text() const;
	void text_color(const color c);
	color text_color() const;
private:
	virtual void on_draw(const draw_event& event);
	string    _text;
	color     _text_color;
	click_box box;
};

typedef shared_ptr<check_box> check_box_ptr;

}
}

#endif
