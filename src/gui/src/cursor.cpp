/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../cursor.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::cursor::cursor(manager& m, const point start, const dim sz)
: sprite(m.get_sprite_system(), start, sz, skin::cursor_name),
  mouse_min(0,0),
  mouse_max(1,1),
  is_pressed(false)
{}

void sge::gui::cursor::pressed(const bool p)
{
	is_pressed = p;
}

void sge::gui::cursor::move(const unit dx, const unit dy)
{
	point p = sprite::pos();
	p.x() += dx;
	p.y() += dy;
	p.x() = std::min(p.x(), mouse_max.x());
	p.x() = std::max(p.x(), mouse_min.x());
	p.y() = std::min(p.y(), mouse_max.y());
	p.y() = std::max(p.y(), mouse_min.y());
	sprite::pos(p);
}

void sge::gui::cursor::draw()
{
	set_texture(is_pressed ? skin::cursor_name : skin::cursor_pressed_name);
	sprite::draw();
}
