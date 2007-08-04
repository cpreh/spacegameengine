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


#include "../sprite.hpp"
#include "../helper.hpp"
#include <cmath>

sge::sprite::sprite(const point p, const dim sz, const virtual_texture_ptr vtex, const color col, const space_unit _z, const space_unit _rotation, const bool vis)
 : p(p),
   sz(sz),
   _z(_z),
   _visible(vis),
   _rotation(_rotation),
   tex(1, vtex),
   use_rot_around(false),
   _repeat(1),
   _color(col)
{}

sge::space_unit& sge::sprite::x()
{
	return p.x();
}

sge::space_unit& sge::sprite::y()
{
	return p.y();
}

sge::sprite::point& sge::sprite::pos()
{
	return p;
}

sge::space_unit& sge::sprite::width()
{
	return sz.w();
}

sge::space_unit& sge::sprite::height()
{
	return sz.h();
}

sge::sprite::dim& sge::sprite::size()
{
	return sz;
}

sge::space_unit& sge::sprite::z()
{
	return _z;
}

void sge::sprite::visible(const bool nvisible)
{
	_visible = nvisible;
}

void sge::sprite::set_texture(const virtual_texture_ptr vtex, const stage_type stage)
{
//	if(stage >= spr_sys->max_tex_level())
//		throw exception("max_tex_level surpassed in sprite::set_texture");
	if(stage >= tex.size())
		tex.resize(stage+1);
	tex[stage] = vtex;
}

void sge::sprite::rotation(const space_unit rot)
{
	_rotation = rot;
}

void sge::sprite::rotate_around(const point p)
{
	use_rot_around = true;
	_rot_around = p;
}

void sge::sprite::rotate_around()
{
	use_rot_around = false;
}

void sge::sprite::repeat(const space_unit r)
{
	_repeat = r;
}

void sge::sprite::set_color(const color c)
{
	_color = c;
}

const sge::space_unit& sge::sprite::x() const
{
	return p.x();
}

const sge::space_unit& sge::sprite::y() const
{
	return p.y();
}

const sge::sprite::point& sge::sprite::pos() const
{
	return p;
}

const sge::space_unit& sge::sprite::width() const
{
	return sz.w();
}

const sge::space_unit& sge::sprite::height() const
{
	return sz.h();
}

const sge::sprite::dim& sge::sprite::size() const
{
	return sz;
}

const sge::space_unit& sge::sprite::z() const
{
	return _z;
}

bool sge::sprite::visible() const
{
	return _visible;
}

sge::sprite::point sge::sprite::center() const
{
	return  point(x() + width() / 2, y() + height() / 2);
}

sge::space_unit sge::sprite::rotation() const
{
	return _rotation;
}

sge::space_unit sge::sprite::repeat() const
{
	return _repeat;
}

sge::color sge::sprite::get_color() const
{
	return _color;
}

const sge::virtual_texture_ptr sge::sprite::get_texture(const stage_type stage) const
{
	if(stage >= tex.size())
		return virtual_texture_ptr();
	return tex[stage];
}

sge::space_unit sge::sprite::radius() const
{
	return std::max(std::sqrt(center().x() * center().x() + x()*x()), std::sqrt(center().y() * center().y() + y()*y()));
}

sge::math::rect sge::sprite::get_rect() const
{
	return math::rect(pos(),size());
}

sge::math::rect sge::sprite::bounding_quad() const
{
	if(rotation() == 0)
		return get_rect();
	const space_unit rad = radius();
	return math::rect(center().x() - rad, center().y() - rad, center().x() + rad, center().y() + rad);
}

sge::circle sge::sprite::bounding_circle() const
{
	return circle(center(),radius());
}

const sge::sprite::point sge::sprite::rotation_center() const
{
	if(!use_rot_around)
		return center();
	return _rot_around;
}

bool sge::sprite::equal(const sprite& l, const sprite& r)
{
	return l.visible() == r.visible() &&
	       l.z() == r.z() &&
	       l.tex == r.tex;
}

bool sge::sprite::less(const sprite& l, const sprite& r)
{
	const bool lvis = l.visible(), rvis = r.visible();
	const space_unit lz = l.z(), rz = r.z();
	const tex_array& ltex = l.tex, &rtex = r.tex;

	return lvis == rvis ?
			lz == rz ?
	                	ltex == rtex ?
	                        	     false
		                : ltex < rtex
		       : lz > rz
		: lvis > rvis;
}
