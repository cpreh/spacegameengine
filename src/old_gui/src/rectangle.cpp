/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../rectangle.hpp"

sge::gui::rectangle::rectangle(manager& m, element* const parent, const point pos, const dim sz, const std::string& tex, const bool visible, const bool enabled)
: element(m,parent,visible,enabled),
  sprite(m.get_sprite_system(),point(),sz,tex),
  rel_pos(pos)
{}

bool sge::gui::rectangle::intersects(const point p) const
{
	return math::intersects(rect(x(),y(),x()+width(),y()+height()),p);
}

void sge::gui::rectangle::on_draw(const draw_event& e)
{
	sprite::pos() = e.pos();
	sprite::draw();
}


const sge::gui::unit& sge::gui::rectangle::x() const
{
	return rel_pos.x();
}

sge::gui::unit& sge::gui::rectangle::x()
{
	return rel_pos.x();
}

const sge::gui::unit& sge::gui::rectangle::y() const
{
	return rel_pos.y();
}

sge::gui::unit& sge::gui::rectangle::y()
{
	return rel_pos.y();
}

const sge::gui::point& sge::gui::rectangle::pos() const
{
	return rel_pos;
}

sge::gui::point& sge::gui::rectangle::pos()
{
	return rel_pos;
}
	
sge::gui::point sge::gui::rectangle::relative_pos() const
{
	return pos();
}
