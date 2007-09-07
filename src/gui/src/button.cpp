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
: widget(parent, name), bg(bg) {}

void sge::gui::button::on_paint(const events::paint_event &pe) {
	update();

	canvas &dest        = pe.dest;
	const point &origin = pe.position;

	dest.fill_rect(rect(origin, size_), bg);

	point
		tl = origin,
		tr = origin + point(size_.w-1, 0),
		bl = origin + point(0, size_.h-1),
		br = point(tr.x, bl.y);

	dest.draw_line(mixing_policy::normal(),
		bl, br, color(0, 0, 0, 128));
	dest.draw_line(mixing_policy::normal(),
		br+point(0,-1), tr, color(0, 0, 0, 128));

	dest.draw_line(mixing_policy::normal(),
		bl+point(1,-1), br+point(-1,-1), color(0, 0, 0, 64));
	dest.draw_line(mixing_policy::normal(),
		br+point(-1,-2), tr+point(-1,1), color(0, 0, 0, 64));

	dest.draw_line(mixing_policy::normal(),
		tl, tr, color(255, 255, 255, 128));
	dest.draw_line(mixing_policy::normal(),
		tl+point(0,1), bl, color(255, 255, 255, 128));

	dest.draw_line(mixing_policy::normal(),
		tl+point(1,1), tr+point(-1,1), color(255, 255, 255, 64));
	dest.draw_line(mixing_policy::normal(),
		tl+point(1,2), bl+point(1,-1), color(255, 255, 255, 64));

	widget::on_paint(pe);
}
