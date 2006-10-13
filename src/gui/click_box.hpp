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


#ifndef SGE_GUI_CLICK_BOX_HPP_INCLUDED
#define SGE_GUI_CLICK_BOX_HPP_INCLUDED

#include "./types.hpp"
#include "./rectangle.hpp"

namespace sge
{
namespace gui
{

class manager;

class click_box : public rectangle {
public:
	enum style { round, quad };
	click_box(manager& man, element* parent, point pos, style s = quad, bool value = false, bool visible = true, bool enabled = true);
	bool value() const;
	static const dim sz;
private:
	virtual void on_click(const mouse_button_event& event);
	virtual void on_draw(const draw_event& event);
	style s;
	bool  v;
};

typedef shared_ptr<click_box> click_box_ptr;

}
}

#endif
