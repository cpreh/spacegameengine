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
#include <cmath>

sge::sprite::sprite(sprite_system& spr_sys, const point p, const dim sz, const std::string& name, const color col, const space_unit _z, const space_unit _rotation, const bool vis)
 : p(p),
   sz(sz),
   _z(_z),
   _visible(vis),
   _rotation(_rotation),
   spr_sys(spr_sys),
   tex(1,spr_sys.vtexture(name)),
   vb_pos(spr_sys.free_vb_pos()),
   my_place(spr_sys.attach(*this)),
   _use_rot_around(false),
   _repeat(1),
   _color(rgba_to_abgr(col))
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

sge::space_unit& sge::sprite::x()
{
	return p.x();
}

sge::space_unit& sge::sprite::y()
{
	return p.y();
}

sge::point& sge::sprite::pos()
{
	return p;
}

sge::space_unit& sge::sprite::width()
{
	return sz.w;
}

sge::space_unit& sge::sprite::height()
{
	return sz.h;
}

sge::dim& sge::sprite::size()
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

void sge::sprite::set_texture(const std::string& name, const stage_type stage)
{
	if(stage >= spr_sys.max_tex_level())
		throw std::runtime_error("max_tex_level surpassed in sprite::set_texture");
	if(stage >= tex.size())
		tex.resize(stage+1);
	tex[stage] = spr_sys.vtexture(name);
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

const sge::space_unit& sge::sprite::x() const
{
	return p.x();
}

const sge::space_unit& sge::sprite::y() const
{
	return p.y();
}

const sge::point& sge::sprite::pos() const
{
	return p;
}

const sge::space_unit& sge::sprite::width() const
{
	return sz.w;
}

const sge::space_unit& sge::sprite::height() const
{
	return sz.h;
}

const sge::dim& sge::sprite::size() const
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
	if(rotation() == 0)
		fill_sprite_position(it, get_rect(), z());
	else
		fill_sprite_position_rotated(it, get_rect(), rotation(), _use_rot_around ? _rot_around : center(), z());

	for(tex_array::size_type i = 0; i < tex.size() && tex[i]; ++i)
		fill_sprite_tex_coordinates(it, tex[i]->area_texc(repeat()), i);

	fill_sprite_color(it, _color);
}

sge::index_buffer::iterator sge::sprite::update_ib(const index_buffer::iterator it)
{
	return fill_sprite_indices(it,vb_pos);
}

void sge::sprite::draw()
{
	if(!visible())
		return;

	{
		sprite_system::vb_buf_type& buf = spr_sys._sprite_vb_buf;
		update_where(spr_sys.vb->create_iterator(buf.data()));
		spr_sys.vb->set_data(buf.data(), vb_pos, detail::vertices_per_sprite);
	}
	
	{
		sprite_system::ib_buf_type& buf = spr_sys._sprite_ib_buf;
		update_ib(buf.c_array());
		spr_sys.ib->set_data(buf.data(), 0, detail::indices_per_sprite);
	}

	spr_sys.set_parameters();
	
	for(tex_array::size_type i = 0; i < tex.size(); ++i)
		spr_sys.get_renderer()->set_texture(get_texture(i),i);

	spr_sys.get_renderer()->render(spr_sys.vb,spr_sys.ib,0,4,PT_Triangle,2);
	
	for(tex_array::size_type i = 1; i < tex.size(); ++i)
		spr_sys.get_renderer()->set_texture(texture_ptr(),i);
}

sge::texture_ptr sge::sprite::get_texture(const stage_type stage) const
{
	if(stage >= tex.size())
		return texture_ptr();
	const const_virtual_texture_ptr p = tex[stage];
	return p ? p->my_texture() : texture_ptr();
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
