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


#include "../manager.hpp"
#include "../types.hpp"

sge::gui::manager *sge::gui::manager::top_level_widget() { return this; }

void sge::gui::manager::resize(dim2 newsize) {
	widget::resize(newsize);
	framebuffer.resize(newsize, false);
}

void sge::gui::manager::focus(widget *w) {
	if (w == this) w = 0; // don't allow focusing of manager widget
	if (w == currently_focused_widget)
		return;
	events::focus_event fe;
		fe.lostfocus = currently_focused_widget;
		fe.gotfocus  = currently_focused_widget = w;

	if (fe.lostfocus)
		fe.lostfocus->on_blur(fe);
	if (fe.gotfocus)
		fe.gotfocus->on_focus(fe);
}

void sge::gui::manager::blur (widget *w) {
	if (w == currently_focused_widget)
		focus(0);
}
