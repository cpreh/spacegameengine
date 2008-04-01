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
namespace sprite
{

extern const dim texture_dim;

class object {
public:
	object(
		point pos,
		virtual_texture_ptr tex,
		dim sz = texture_dim,
		color c = colors::white,
		depth_type z = 0,
		rotation_type rotation = 0,
		bool visible = true);

	unit& x();
	unit& y();
	point& pos();
	unit& w();
	unit& h();
	dim& size();
	depth_type& z();
	void visible(bool visible);
	void set_texture(virtual_texture_ptr);
	void rotation(rotation_type rot);
	void rotate_around(point p);
	void rotate_around();
	void repeat(repetition_type);
	void set_color(color c);
	void set_center(const point &);
	
	const unit& x() const;
	const unit& y() const;
	const depth_type& z() const;
	const point& pos() const;
	const unit& w() const;
	const unit& h() const;
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

	static bool equal(const object& l, const object& r);
	static bool less(const object& l, const object& r);
private:
	point               pos_;
	dim                 size_;
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
}

#endif
