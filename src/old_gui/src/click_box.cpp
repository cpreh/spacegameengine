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


#include "../click_box.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::click_box::click_box(manager& man, element* const parent, const point p, const style s, const bool v, const bool visible, const bool enabled)
: rectangle(man,parent,p,sz,texture_map::no_texture,visible,enabled),
  s(s), v(v)
{}

void sge::gui::click_box::on_click(const mouse_button_event&)
{
	v = !v;
}

void sge::gui::click_box::on_draw(const draw_event& event)
{
	switch(s) {
	case round:
		set_texture(v ? skin::clickbox_round_pressed_name : skin::clickbox_round_name);
		break;
	case quad:
		set_texture(v ? skin::clickbox_quad_pressed_name : skin::clickbox_quad_name);
		break;
	}
	rectangle::on_draw(event);
}

bool sge::gui::click_box::value() const
{
	return v;
}

const sge::gui::dim sge::gui::click_box::sz(0.03f,0.03f);
