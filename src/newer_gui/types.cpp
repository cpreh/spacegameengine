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

#include <sge/gui/types.hpp>

sge::gui::point sge::gui::point::normalize(const sge::gui::rect &area) const {
	return point(
		(x >= area.x + area.w) ? area.x + area.w - 1 : ((x < area.x) ? 0 : x),
		(y >= area.y + area.h) ? area.y + area.h - 1 : ((y < area.y) ? 0 : y)
	);
}

inline sge::gui::fpoint sge::gui::fpoint::normalize(const sge::gui::frect &area) const {
	return fpoint(
		(x >= area.x + area.w) ? area.x + area.w : ((x < area.x) ? 0 : x),
		(y >= area.y + area.h) ? area.y + area.h : ((y < area.y) ? 0 : y)
	);
}
