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


#include "../../math/compare.hpp"
#include "../../math/rect_impl.hpp"
#include "../../math/circle_impl.hpp"
#include "../sprite.hpp"
#include "../helper.hpp"
#include <cmath>
#include <limits>

const sge::sprite_dim sge::sprite_texture_dim(std::numeric_limits<sprite_unit>::max(),std::numeric_limits<sprite_unit>::max());

sge::sprite::sprite(const point p,
                    const virtual_texture_ptr vtex,
                    const dim sz,
                    const color color_,
                    const depth_type z_,
                    const rotation_type rotation_,
                    const bool visible_)
 : p(p),
   sz(sz == sprite_texture_dim ? dim(static_cast<sprite_unit>(vtex->area().w()),static_cast<sprite_unit>(vtex->area().h())) : sz),
   z_(z_),
   rotation_(rotation_),
   tex(vtex),
   rot_around_(),
   repeat_(1),
   color_(color_),
   visible_(visible_),
   use_rot_around(false)
{}

sge::sprite_unit& sge::sprite::x()
{
	return p.x();
}

sge::sprite_unit& sge::sprite::y()
{
	return p.y();
}

sge::sprite::point& sge::sprite::pos()
{
	return p;
}

sge::sprite_unit& sge::sprite::width()
{
	return sz.w();
}

sge::sprite_unit& sge::sprite::height()
{
	return sz.h();
}

sge::sprite::dim& sge::sprite::size()
{
	return sz;
}

sge::sprite::depth_type& sge::sprite::z()
{
	return z_;
}

void sge::sprite::visible(const bool nvisible)
{
	visible_ = nvisible;
}

void sge::sprite::set_texture(const virtual_texture_ptr vtex)
{
	tex = vtex;
}

void sge::sprite::rotation(const rotation_type rot)
{
	rotation_ = rot;
}

void sge::sprite::rotate_around(const point p)
{
	use_rot_around = true;
	rot_around_ = p;
}

void sge::sprite::rotate_around()
{
	use_rot_around = false;
}

void sge::sprite::repeat(const repetition_type r)
{
	repeat_ = r;
}

void sge::sprite::set_color(const color c)
{
	color_ = c;
}

const sge::sprite_unit& sge::sprite::x() const
{
	return p.x();
}

const sge::sprite_unit& sge::sprite::y() const
{
	return p.y();
}

const sge::sprite::point& sge::sprite::pos() const
{
	return p;
}

const sge::sprite_unit& sge::sprite::width() const
{
	return sz.w();
}

const sge::sprite_unit& sge::sprite::height() const
{
	return sz.h();
}

const sge::sprite::dim& sge::sprite::size() const
{
	return sz;
}

const sge::sprite::depth_type& sge::sprite::z() const
{
	return z_;
}

bool sge::sprite::visible() const
{
	return visible_;
}

sge::sprite::point sge::sprite::center() const
{
	return  point(x() + width() / 2, y() + height() / 2);
}

sge::sprite::rotation_type sge::sprite::rotation() const
{
	return rotation_;
}

sge::sprite::repetition_type sge::sprite::repeat() const
{
	return repeat_;
}

sge::color sge::sprite::get_color() const
{
	return color_;
}

const sge::virtual_texture_ptr sge::sprite::get_texture() const
{
	return tex;
}

sge::space_unit sge::sprite::radius() const
{
	return std::max(std::sqrt(static_cast<space_unit>(center().x() * center().x() + x() * x())),
	                std::sqrt(static_cast<space_unit>(center().y() * center().y() + y() * y()))
	               );
}

sge::sprite::rect sge::sprite::get_rect() const
{
	return rect(pos(),size());
}

sge::sprite::rect sge::sprite::bounding_quad() const
{
	if(math::almost_zero(rotation()))
		return get_rect();
	const space_unit rad = radius();
	return rect(static_cast<sprite_unit>(static_cast<space_unit>(center().x()) - rad),
	            static_cast<sprite_unit>(static_cast<space_unit>(center().y()) - rad),
	            static_cast<sprite_unit>(static_cast<space_unit>(center().x()) + rad),
	            static_cast<sprite_unit>(static_cast<space_unit>(center().y()) + rad));
}

sge::math::circle sge::sprite::bounding_circle() const
{
	return math::circle(
		static_cast<math::circle::value_type>(x()),
		static_cast<math::circle::value_type>(y()),
		radius());
}

const sge::sprite::point sge::sprite::rotation_center() const
{
	if(!use_rot_around)
		return center();
	return pos() + rot_around_;
}

bool sge::sprite::equal(const sprite& l, const sprite& r)
{
	return l.visible() == r.visible() &&
	       math::compare(l.z(), r.z()) &&
	       l.tex == r.tex;
}

bool sge::sprite::less(const sprite& l, const sprite& r)
{
	const bool lvis = l.visible(), rvis = r.visible();
	const depth_type lz = l.z(), rz = r.z();
	const virtual_texture_ptr ltex = l.get_texture(), &rtex = r.get_texture();

	return lvis == rvis ?
			math::compare(lz, rz) ?
	                	ltex == rtex ?
	                        	     false
		                : ltex < rtex
		       : lz > rz
		: lvis > rvis;
}
