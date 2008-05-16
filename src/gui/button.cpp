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

#include <sge/gui/button.hpp>

sge::gui::button::button(widget * const parent, const std::string &name)
: widget(parent, name), hover(false), pushed(false) {}

void sge::gui::button::perform_resize(dim2 newsize) {
	framebuffer.resize(newsize, false);
	widget::perform_resize(newsize);
}

sge::gui::widget::event_return_type sge::gui::button::on_mouse_move(const events::mouse_event &) { return this; }
sge::gui::widget::event_return_type sge::gui::button::on_mouse_over(const events::mouse_event &) { hover = true ; change(); return this; }
sge::gui::widget::event_return_type sge::gui::button::on_mouse_out (const events::mouse_event &) { hover = false; change(); return this; }

sge::gui::widget::event_return_type sge::gui::button::on_mouse_up  (const events::mouse_event &me) {
	if (pushed && me.pressed == events::mouse_event::LEFT) {
		if (hover) {
			clicked();
			change();
		}
		pushed = false;
	}
	return this;
}

sge::gui::widget::event_return_type sge::gui::button::on_mouse_down(const events::mouse_event &me) {
	if (me.is_focus_injection) return this;
	if (me.pressed == events::mouse_event::LEFT) {
		focus();
		pushed = true;
		change();
	}
	return this;
}

// we want to allow focussing, therefore we have to override the autoblur of widget
void sge::gui::button::on_focus(const events::focus_event &) {}

void sge::gui::button::on_blur(const events::focus_event &) {
	if (pushed) {
		pushed = false;
		change();
	}
}

void sge::gui::button::on_paint(const events::paint_event &pe) {
	pe.dest.blit<mixing_policy::normal>(framebuffer, rect(point(0,0), size()), pe.position);
}

void sge::gui::button::on_update() {
	framebuffer.fill(sge::colors::transparent);

	skin_ptr sty = drawskin();

	sty->draw_background(
		this,
		skin::border_style::button,
		hover
			? pushed
				? skin::focus_modifier::hover_active
				: skin::focus_modifier::hover
			: skin::focus_modifier::none,
		rect(point(0,0), size()),
		framebuffer
	);

	sty->draw_border(
		this,
		skin::border_style::button,
		hover
			? pushed
				? skin::focus_modifier::hover_active
				: skin::focus_modifier::hover
			: skin::focus_modifier::none,
		rect(point(0,0), size()),
		framebuffer
	);
}
