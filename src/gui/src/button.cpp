/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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

#include "../button.hpp"

sge::gui::button::button(widget *parent, color bg, std::string name)
: widget(parent, name), bg(bg), hover(false), pushed(false) {}

sge::gui::widget::event_return_type sge::gui::button::on_mouse_move(const events::mouse_event &) { return this; }
sge::gui::widget::event_return_type sge::gui::button::on_mouse_over(const events::mouse_event &) { hover = true ; change(); return this; }
sge::gui::widget::event_return_type sge::gui::button::on_mouse_out (const events::mouse_event &) { hover = false; change(); return this; }

sge::gui::widget::event_return_type sge::gui::button::on_mouse_up  (const events::mouse_event &me) {
	if (pushed && me.pressed == events::mouse_event::LEFT) {
		clicked();
		pushed = false;
		change();
	}
	return this;
}

sge::gui::widget::event_return_type sge::gui::button::on_mouse_down(const events::mouse_event &me) {
	if (me.pressed == events::mouse_event::LEFT) {
		pushed = true;
		change();
	}
	return this;
}

void sge::gui::button::on_paint(const events::paint_event &pe) {
	color c = bg;
	c.mix<mixing_policy::normal>(sge::colors::white, hover ? .25 : 0);
	pe.dest.fill_rect(rect(pe.position, size()), c);

	color c1 = pushed ? sge::colors::black : sge::colors::white;
	color c2 = pushed ? sge::colors::white : sge::colors::black;
	mixing_policy::normal mix;

	c1.a = c2.a = color::MAX_VALUE / 2;
	pe.dest.draw_line(mix, pe.position+point(0,0), pe.position+point(0, size().h-1), c1);
	pe.dest.draw_line(mix, pe.position+point(1,0), pe.position+point(size().w-1, 0), c1);
	pe.dest.draw_line(mix, pe.position+point(size().w-1, size().h-1), pe.position+point(size().w-1, 1), c2);
	pe.dest.draw_line(mix, pe.position+point(size().w-2, size().h-1), pe.position+point(1, size().h-1), c2);

	c1.a /= 2; c2.a /= 2;
	pe.dest.draw_line(mix, pe.position+point(1,1), pe.position+point(1, size().h-2), c1);
	pe.dest.draw_line(mix, pe.position+point(2,1), pe.position+point(size().w-2, 1), c1);
	pe.dest.draw_line(mix, pe.position+point(size().w-2, size().h-2), pe.position+point(size().w-1, 2), c2);
	pe.dest.draw_line(mix, pe.position+point(size().w-3, size().h-2), pe.position+point(2, size().h-1), c2);
}
