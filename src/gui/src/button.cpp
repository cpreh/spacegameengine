/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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

#include "../button.hpp"

sge::gui::button::button(widget *parent, color bg, std::string name)
: widget(parent, name), bg(bg) {}

void sge::gui::button::on_paint(const events::paint_event &pe) {
	update();

	canvas &dest        = pe.dest;
	const point &origin = pe.position;

	dest.fill_rect(rect(origin, size_), bg);

	pe.dest.draw_line(
		mixing_policy::normal(),
		origin + point(size_.w-1, 0),
		origin + point(size_.w-1, size_.h-1),
		color(0,0,0, 128)
	);
	pe.dest.draw_line(
		mixing_policy::normal(),
		origin + point(0        , size_.h-1),
		origin + point(size_.w-2, size_.h-1),
		color(0,0,0, 128)
	);
	pe.dest.draw_line(
		mixing_policy::normal(),
		origin + point(size_.w-2, 1),
		origin + point(size_.w-2, size_.h-2),
		color(0,0,0, 192)
	);
	pe.dest.draw_line(
		mixing_policy::normal(),
		origin + point(1        , size_.h-2),
		origin + point(size_.w-3, size_.h-2),
		color(0,0,0, 192)
	);

	pe.dest.draw_line(
		mixing_policy::normal(),
		origin + point(0, 0),
		origin + point(0, size_.h-1),
		color(255,255,255, 128)
	);
	pe.dest.draw_line(
		mixing_policy::normal(),
		origin + point(1        , size_.h-1),
		origin + point(size_.w-1, size_.h-1),
		color(255,255,255, 128)
	);
	pe.dest.draw_line(
		mixing_policy::normal(),
		origin + point(1, 1),
		origin + point(1, size_.h-2),
		color(255,255,255, 192)
	);
	pe.dest.draw_line(
		mixing_policy::normal(),
		origin + point(2        , size_.h-2),
		origin + point(size_.w-3, size_.h-2),
		color(255,255,255, 192)
	);

	widget::on_paint(pe);
}
