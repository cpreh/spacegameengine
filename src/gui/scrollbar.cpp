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


#include <sge/gui/scrollbar.hpp>

sge::gui::scrollbar::drawer::drawer(widget * const parent, const std::string &name)
: button(parent, name) {}
sge::gui::widget::event_return_type sge::gui::scrollbar::drawer::on_mouse_move(const events::mouse_event &) { return this; }

void sge::gui::scrollbar::drawer::on_update() {
	skin_ptr sty = drawskin();
	skin::focus_modifier::type fm = hover
		? pushed
			? skin::focus_modifier::hover
			: skin::focus_modifier::hover_active
		: skin::focus_modifier::none;

	sty->draw_background(
		this,
		skin::border_style::scrolldrawer,
		fm,
		rect(point(0,0), size()),
		framebuffer
	);

	{ events::paint_event pe = { framebuffer, point(0,0) };
		paint_children(pe);
	}

	sty->draw_border(
		this,
		skin::border_style::scrolldrawer,
		fm,
		rect(point(0,0), size()),
		framebuffer
	);
}


sge::gui::scrollbar::scrollbar(widget * const parent, const skin::scroll_direction::type sdt, const std::string &name)
: widget(parent, name)
, direction(sdt)
, draw     (this, name.empty() ? name : name+":drawer")
, upleft   (this, (sdt==skin::scroll_direction::vertical) ? skin::stock_icon::up   : skin::stock_icon::left , name.empty() ? name : name+":upleft")
, downright(this, (sdt==skin::scroll_direction::vertical) ? skin::stock_icon::down : skin::stock_icon::right, name.empty() ? name : name+":downright") {
	step.small = 1;
	step.large = 10;
	range.min  = 0;
	range.max  = 100;
	resize(100, 100);
}

void sge::gui::scrollbar::min(value_type newmin) {
	if (range.min == newmin) return;
	range.min = newmin;
	if (range.min < val) value(range.min);
	else                 value(1+--val);
}

void sge::gui::scrollbar::max(value_type newmax) {
	if (range.max == newmax) return;
	range.max = newmax;
	if (range.max < val) value(range.max);
	else                 value(1+--val);
}

void sge::gui::scrollbar::value(value_type newval) {
	if (newval == val) return;
	val = newval;
	modified_preview(val);
	modified        (val);
	change();
}

void sge::gui::scrollbar::perform_resize(dim2 newsize) {
	if ((direction == skin::scroll_direction::horizontal) && (newsize.h != upleft.size().h))
		resize(newsize.w, upleft.size().h);
	else if ((direction == skin::scroll_direction::vertical) && (newsize.w != upleft.size().w))
		resize(upleft.size().w, newsize.h);
	else {
		framebuffer.resize(newsize, false);
		widget::perform_resize(newsize);
		value(1+--val);
	}
}

void sge::gui::scrollbar::on_update() {
	framebuffer.fill(sge::colors::transparent);

	drawskin()->draw_background(
		this,
		skin::border_style::scrollbar,
		skin::focus_modifier::none,
		rect(point(0,0), size()),
		framebuffer
	);

	{ events::paint_event pe = { framebuffer, point(0,0) };
		paint_children(pe);
	}
}
