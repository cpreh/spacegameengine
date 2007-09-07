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

sge::gui::manager::manager()
: sge::gui::widget() {}

sge::gui::manager::manager(sge::gui::dim2 size)
: sge::gui::widget() {
	resize(size);
}

sge::gui::manager::~manager() {}

sge::gui::manager *sge::gui::manager::top_level_widget() const {
	return const_cast<manager*>(this);
}

void sge::gui::manager::resize(sge::gui::dim2 newsize) {
	widget::resize(newsize);
	framebuffer.resize(newsize, false);
}

sge::virtual_texture_ptr sge::gui::manager::to_texture(sge::texture_manager &texmgr) {
	if (flags.changed) {
		framebuffer.fill(sge::colors::transparent);
		events::paint_event pe = { framebuffer, point(0,0) };
		on_paint(pe);
		last_texture = framebuffer.to_texture(texmgr, last_texture);
	}
	return last_texture;
}
