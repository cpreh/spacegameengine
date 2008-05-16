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


#include <sge/gui/manager.hpp>

#include <sge/gui/defaultskin.hpp>
#include <sge/gui/types.hpp>

void sge::gui::manager::init() {
	skin(defaultskin::get());
	previously_hovered_widget = 0;
	currently_focused_widget  = 0;
	show();
}

sge::gui::manager::manager()
: sge::gui::widget() { init(); }

sge::gui::manager::manager(const sge::gui::dim2 &size)
: sge::gui::widget() {
	resize(size);
	init();
}

sge::gui::manager::manager(inputprocessor &ip)
: sge::gui::widget()
, inputacceptor(ip) {
	resize(ip.get_clipping().size());
	move  (ip.get_clipping().position());
	init();
}

sge::gui::manager::manager(inputprocessor &ip, const point &p, const dim2 &s)
: sge::gui::widget()
, inputacceptor(ip) {
	resize(s);
	move  (p);
	init();
}

sge::gui::manager::manager(inputprocessor &ip, const rect &r)
: sge::gui::widget()
, inputacceptor(ip) {
	resize(r.size());
	move  (r.position());
	init();
}

sge::gui::manager::~manager() {}

sge::virtual_texture_ptr sge::gui::manager::to_texture(sge::texture_manager &texmgr) {
	if ((!last_texture) || changed()) {
		framebuffer.fill(sge::colors::transparent);
		events::paint_event pe = { framebuffer, point(0,0) };
		paint(pe);
		last_texture = framebuffer.to_texture(texmgr, last_texture);
	}
	return last_texture;
}

void sge::gui::manager::free_texture() {
	last_texture = sge::virtual_texture_ptr();
}

void sge::gui::manager::widget_removed(sge::gui::widget *w) {
	if (previously_hovered_widget == w)
		previously_hovered_widget = 0;
	if (currently_focused_widget == w)
		currently_focused_widget = 0;
}
