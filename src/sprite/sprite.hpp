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


#ifndef SGE_SPRITE_HPP_INCLUDED
#define SGE_SPRITE_HPP_INCLUDED

#include "../math/rect.hpp"
#include "../math/vector.hpp"
#include "../math/dim.hpp"
#include "../math/circle.hpp"
#include "../texture/virtual_texture.hpp"
#include "../renderer/colors.hpp"
#include "types.hpp"

namespace sge
{
extern const sprite_dim sprite_texture_dim;

class sprite {
public:
	typedef sprite_point             point;
	typedef sprite_dim               dim;
	typedef sprite_rect              rect;
	typedef sprite_depth_type        depth_type;
	typedef sprite_rotation_type     rotation_type;
	typedef sprite_repetition_type   repetition_type;

	sprite(point pos,
	       virtual_texture_ptr tex,
	       dim sz = sprite_texture_dim,
	       color c = colors::white,
	       depth_type z = 0,
	       rotation_type rotation = 0,
	       bool visible = true);

	sprite_unit& x();
	sprite_unit& y();
	point& pos();
	sprite_unit& width();
	sprite_unit& height();
	dim& size();
	depth_type& z();
	void visible(bool visible);
	void set_texture(virtual_texture_ptr);
	void rotation(rotation_type rot);
	void rotate_around(point p);
	void rotate_around();
	void repeat(repetition_type);
	void set_color(color c);
	
	const sprite_unit& x() const;
	const sprite_unit& y() const;
	const depth_type& z() const;
	const point& pos() const;
	const sprite_unit& width() const;
	const sprite_unit& height() const;
	const dim& size() const;
	bool visible() const;
	rect get_rect() const;
	point center() const;
	rotation_type rotation() const;
	space_unit radius() const;
	repetition_type repeat() const;
	color get_color() const;
	rect bounding_quad() const;
	math::circle bounding_circle() const;
	const point rotation_center() const;
	const virtual_texture_ptr get_texture() const;

	static bool equal(const sprite& l, const sprite& r);
	static bool less(const sprite& l, const sprite& r);
private:
	point               p;
	dim                 sz;
	depth_type          z_;
	rotation_type       rotation_;
	virtual_texture_ptr tex;
	point               rot_around_;
	repetition_type     repeat_;
	color               color_;
	bool                visible_;
	bool                use_rot_around;
};

}
#endif

