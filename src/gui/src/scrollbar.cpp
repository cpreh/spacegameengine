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


#include "../scrollbar.hpp"

sge::gui::scrollbar::drawer::drawer(widget *parent, std::string name);
sge::gui::events::event_return_type sge::gui::scrollbar::drawer::on_mouse_move(const events::mouse_event &);
void sge::gui::scrollbar::drawer::on_update();


sge::gui::scrollbar::scrollbar(widget *parent, skin::scroll_direction::type sdt, std::string name)
: widget(parent, name)
, direction(sdt)
, upleft   (this, (sdt==skin::scroll_direction::vertical) ? skin::stock_icon::up   : sking::stock_icon::left , name.empty() ? name : name+":upleft")
, downright(this, (sdt==skin::scroll_direction::vertical) ? skin::stock_icon::down : sking::stock_icon::right, name.empty() ? name : name+":downright")
{
	resize(100, 100);
}

void sge::gui::scrollbar::min(value_type newmin) {
	if (range.min == newmin) return;
	range.min = newmin;
	if (min < val) value(min);
	else           value(1+--val);
}

void sge::gui::scrollbar::max(value_type newmax) {
	if (range.max == newmax) return;
	range.max = newmax;
	if (max < val) value(max);
	else           value(1+--val);
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

	skin_ptr sty = drawskin();

	sty->
}
