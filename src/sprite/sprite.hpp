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


#ifndef SGE_SPRITE_HPP_INCLUDED
#define SGE_SPRITE_HPP_INCLUDED

#include <string>
#include <vector>
#include "../math/rect.hpp"
#include "../math/vector2.hpp"
#include "../math/dim.hpp"
#include "../math/rect.hpp"
#include "../math/circle.hpp"
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/texture.hpp"
#include "../math/circle.hpp"
#include "../texture/virtual_texture.hpp"
#include "sprite_fwd.hpp"

namespace sge
{

class sprite {
public:
	sprite(sprite_system& s, point pos, dim sz, const std::string& tex, color c = colors::white, space_unit z = 0, space_unit rotation = 0, bool visible = true);
	sprite(const sprite& s);
	sprite& operator=(const sprite&);

	space_unit& x();
	space_unit& y();
	point& pos();
	space_unit& width();
	space_unit& height();
	dim& size();
	space_unit& z();
	void visible(bool visible);
	void set_texture(const std::string& name, stage_type stage = 0);
	void rotate(space_unit rot);
	void rotate_around(point p);
	void rotate_around();
	void repeat(space_unit);
	void set_color(color c);
	
	const space_unit& x() const;
	const space_unit& y() const;
	const space_unit& z() const;
	const point& pos() const;
	const space_unit& width() const;
	const space_unit& height() const;
	const dim& size() const;
	bool visible() const;
	rect get_rect() const;
	point center() const;
	space_unit rotation() const;
	space_unit radius() const;
	space_unit repeat() const;
	color get_color() const;
	rect bounding_quad() const;
	circle bounding_circle() const;

	void draw();
	~sprite();

	static bool equal(const sprite& l, const sprite& r);
	static bool less(const sprite& l, const sprite& r);
private:
	friend class sprite_system;
	friend class sprite_drawer;

	texture_ptr get_texture(stage_type stage) const;
	void update_where(vertex_buffer::iterator where);
	void update();
	index_buffer::iterator update_ib(index_buffer::iterator where);

	point p;
	dim sz;
	space_unit _z;
	bool _visible;
	space_unit _rotation;
	sprite_system* spr_sys;
	typedef std::vector<const_virtual_texture_ptr> tex_array;
	tex_array tex;
	vertex_buffer::size_type vb_pos;
	sprite_list::iterator my_place;
	bool _use_rot_around;
	point _rot_around;
	space_unit _repeat;
	color _color;
};

}
#endif

