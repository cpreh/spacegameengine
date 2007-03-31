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


#include "../scrollbar.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::inner_scrollbar::inner_scrollbar(manager& m, element* const parent, const point pos, const dim sz)
: rectangle(m,parent,pos,sz,skin::inner_scrollbar_name)
{}


sge::gui::scroll_button::scroll_button(manager& m, element* const parent, const point pos, const dim sz, const style _style, const action_function action)
: rectangle(m,parent,pos,sz,_style == up_scroll ? skin::up_scrollbutton_name : skin::down_scrollbutton_name), action(action)
{}

void sge::gui::scroll_button::on_mouse_press(const mouse_button_event&)
{
	action(); // FIXME
}

void sge::gui::scroll_button::on_click(const mouse_button_event&)
{
	action();
}

void sge::gui::scroll_button::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
}
