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


#ifndef SGE_GUI_RECTANGLE_HPP_INCLUDED
#define SGE_GUI_RECTANGLE_HPP_INCLUDED

#include "./types.hpp"
#include "./element.hpp"
#include "../sprite/sprite.hpp"

namespace sge
{
namespace gui
{

class manager;

class rectangle : public element, private sprite {
public:
	rectangle(manager& m, element* parent, point pos, dim sz, const std::string& texture_name, bool visible = true, bool enabled = true);
	unit x() const { return rel_pos.x(); }
	void x(const unit _x) { rel_pos.x() = _x; }
	unit y() const { return rel_pos.y(); }
	void y(const unit _y) { rel_pos.y() = _y; }
	point pos() const { return rel_pos; }
	void pos(const point p) { rel_pos = p; }

	using sprite::width;
	using sprite::height;
	using sprite::size;
	using sprite::get_rect;
	using sprite::center;
	using sprite::repeat;
	bool intersects(point p) const;
protected:
	virtual void on_draw(const draw_event& event);
	using sprite::set_texture;
private:
	point relative_pos() const { return rel_pos; }
	point rel_pos;
};

}
}

#endif
