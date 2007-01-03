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
#include "../system.hpp"
#include "../../renderer/lock_ptr.hpp"
#include "../helper.hpp"
#include <boost/array.hpp>
#include <cmath>
#include <iostream>

sge::sprite::sprite(sprite_system& spr_sys, const point p, const dim sz, const unsigned _z, const std::string& name, const space_unit _rotation, const bool vis)
 : p(p),
   sz(sz),
   _z(_z),
   _visible(vis),
   _rotation(_rotation),
   spr_sys(spr_sys),
   tex(spr_sys.vtexture(name)),
   vb_pos(spr_sys.free_vb_pos()),
   my_place(spr_sys.attach(*this)),
   _use_rot_around(false),
   _repeat(1),
   _color(rgba_to_abgr(colors::white))
{}

sge::sprite::sprite(const sprite& spr)
 : p(spr.p),
   sz(spr.sz),
   _z(spr._z),
   _visible(spr._visible),
   _rotation(spr._rotation),
   spr_sys(spr.spr_sys),
   tex(spr.tex),
   vb_pos(spr_sys.free_vb_pos()),
   my_place(spr_sys.attach(*this)),
   _use_rot_around(spr._use_rot_around),
   _rot_around(spr._rot_around),
   _repeat(spr._repeat),
   _color(spr._color)
{}

void sge::sprite::x(const space_unit nx)
{
	p.x() = nx;
}

void sge::sprite::y(const space_unit ny)
{
	p.y() = ny;
}

void sge::sprite::pos(const point np)
{
	p = np;
}

void sge::sprite::width(const space_unit w)
{
	sz.w = w;
}

void sge::sprite::height(const space_unit h)
{
	sz.h = h;
}

void sge::sprite::size(const dim nsz)
{
	sz = nsz;
}

void sge::sprite::z(const unsigned nz)
{
	_z = nz;
}

void sge::sprite::visible(const bool nvisible)
{
	_visible = nvisible;
}

void sge::sprite::set_texture(const std::string& name)
{
	tex = spr_sys.vtexture(name);
}

void sge::sprite::rotate(const space_unit rot)
{
	_rotation = rot;
}

void sge::sprite::rotate_around(const point p)
{
	_use_rot_around = true;
	_rot_around = p;
}

void sge::sprite::rotate_around()
{
	_use_rot_around = false;
}

void sge::sprite::repeat(const space_unit r)
{
	_repeat = r;
}

void sge::sprite::set_color(const color c)
{
	_color = rgba_to_abgr(c);
}

sge::space_unit sge::sprite::x() const
{
	return p.x();
}

sge::space_unit sge::sprite::y() const
{
	return p.y();
}

sge::point sge::sprite::pos() const
{
	return p;
}

sge::space_unit sge::sprite::width() const
{
	return sz.w;
}

sge::space_unit sge::sprite::height() const
{
	return sz.h;
}

sge::dim sge::sprite::size() const
{
	return sz;
}

unsigned sge::sprite::z() const
{
	return _z;
}

bool sge::sprite::visible() const
{
	return _visible;
}

sge::point sge::sprite::center() const
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
	return abgr_to_rgba(_color);
}

sge::sprite::~sprite()
{
	spr_sys.detach(*this);
}

void sge::sprite::update()
{
	update_where(spr_sys.vb->begin()+vb_pos);
}

void sge::sprite::update_where(const vertex_buffer::iterator it)
{
	if(repeat() != 1 && tex->repeatable() == false)
		std::cerr << "Warning: texture not repeatable but sprite repetition is " << repeat() << "!\n";
	const rect tex_rect = get_texture() ? tex_size_to_space_rect(tex->area(), get_texture()->width(), get_texture()->height(), repeat()) : rect();
	if(rotation() == 0)
		fill_sprite_vertices(it, get_rect(), tex_rect);
	else
		fill_sprite_vertices_rotated(it, get_rect(), rotation(), _use_rot_around ? _rot_around : center(), tex_rect);

	fill_sprite_color(it, _color);
}

sge::index_buffer::iterator sge::sprite::update_ib(index_buffer::iterator it)
{
	return fill_sprite_indices(it,vb_pos);
}

void sge::sprite::draw()
{
	if(!tex)
		return;
	
	boost::array<vertex_buffer::value_type,sizeof(space_unit)*5*4> buf; // FIXME: magic constants
	update_where(spr_sys.vb->create_iterator(buf.c_array()));
	spr_sys.vb->set_data(buf.data(),vb_pos,4);
	
	{
	boost::array<index_buffer::value_type, detail::indices_per_sprite> buf;
	update_ib(buf.c_array());
	spr_sys.ib->set_data(buf.data(), 0, detail::indices_per_sprite);
	}

	spr_sys.set_parameters();
	spr_sys.get_renderer()->set_texture(0,get_texture());
	spr_sys.get_renderer()->render(spr_sys.vb,spr_sys.ib,0,4,PT_Triangle,2);
}

sge::texture_ptr sge::sprite::get_texture() const
{
	return tex ? tex->my_texture() : texture_ptr();
}

sge::space_unit sge::sprite::radius() const
{
	return std::max(std::sqrt(center().x() * center().x() + x()*x()), std::sqrt(center().y() * center().y() + y()*y()));
}

sge::rect sge::sprite::get_rect() const
{
	return rect(pos(),size());
}

sge::rect sge::sprite::bounding_quad() const
{
	if(rotation() == 0)
		return get_rect();
	const space_unit rad = radius();
	return rect(center().x() - rad, center().y() - rad, center().x() + rad, center().y() + rad);
}

sge::circle sge::sprite::bounding_circle() const
{
	return circle(center(),radius());
}

bool sge::sprite::equal_texture(const sprite& l, const sprite& r)
{
	return l.get_texture() == r.get_texture();
}

bool sge::sprite::less(const sprite& l, const sprite& r)
{
	const unsigned lz = l.z(), rz = r.z();
	sge::texture_ptr ltex = l.get_texture(), rtex = r.get_texture();

	return lz == rz ?
	                ltex == rtex ? 
	                             false
	                : ltex < rtex
	       : lz < rz;
}

