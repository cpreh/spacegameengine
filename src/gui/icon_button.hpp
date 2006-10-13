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


#ifndef SGE_GUI_ICON_BUTTON_HPP_INCLUDED
#define SGE_GUI_ICON_BUTTON_HPP_INCLUDED

#include "./types.hpp"
#include "./rectangle.hpp"

namespace sge
{
namespace gui
{

class manager;

class icon_button : public rectangle {
public:
	icon_button(manager& m, element* parent, point pos, dim sz, const std::string& texture_released, const std::string& texture_hover,
	            const std::string& texture_pressed, bool visible = true, bool enabled = true);
private:
	virtual void on_draw(const draw_event& event);
	std::string texture_pressed,
	            texture_released,
	            texture_hover;
};

typedef shared_ptr<icon_button> icon_button_ptr;

}
}

#endif
