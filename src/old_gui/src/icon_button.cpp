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


#include "../icon_button.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::icon_button::icon_button(manager& m, element* const parent, const point pos, const dim sz, const std::string& texture_released, const std::string& texture_hover, const std::string& texture_pressed, const bool visible, const bool enabled)
: rectangle(m,parent,pos,sz,texture_released,visible,enabled),
  texture_pressed(texture_pressed), texture_released(texture_released), texture_hover(texture_hover)
{}

void sge::gui::icon_button::on_draw(const draw_event& event)
{
	if(pressed())
		set_texture(texture_pressed);
	else if(m.hover()==this)
		set_texture(texture_hover);
	else
		set_texture(texture_released);
	rectangle::on_draw(event);
}
