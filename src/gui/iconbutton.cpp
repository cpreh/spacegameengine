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

#include <sge/gui/iconbutton.hpp>
#include <sge/renderer/colors.hpp>

sge::gui::iconbutton::iconbutton(widget * const parent, const std::string &name)
: button(parent, name) {
	skin_ptr sty = drawskin();
	resize(sty->adjust_to_border(
		this,
		skin::border_style::iconbutton,
		rect(point(0,0), sty->icon_size())).size()
	);
}

sge::gui::iconbutton::iconbutton(widget * const parent, skin::stock_icon::type ico, std::string name)
: button(parent, name) {
	skin_ptr sty = drawskin();
	resize(sty->adjust_to_border(
		this,
		skin::border_style::iconbutton,
		rect(point(0,0), sty->icon_size())).size()
	);
	icon(ico);
}

void sge::gui::iconbutton::icon(skin::stock_icon::type newicon) {
	if (stockicon == newicon) return;
	stockicon = newicon;
	change();
}

void sge::gui::iconbutton::on_update() {
	framebuffer.fill(sge::colors::transparent);

	skin_ptr sty = drawskin();

	sty->draw_background(
		this,
		skin::border_style::iconbutton,
		hover
			? pushed
				? skin::focus_modifier::hover_active
				: skin::focus_modifier::hover
			: skin::focus_modifier::none,
		rect(point(0,0), size()),
		framebuffer
	);

	sty->draw_icon(
		this,
		stockicon,
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
		skin::border_style::iconbutton,
		hover
			? pushed
				? skin::focus_modifier::hover_active
				: skin::focus_modifier::hover
			: skin::focus_modifier::none,
		rect(point(0,0), size()),
		framebuffer
	);
}
