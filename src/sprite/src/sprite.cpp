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

sge::sprite::sprite(sprite_system& spr_sys, const point p, const dim sz, const unsigned _z, const std::string& name, const space_unit _rotation, const bool vis)
 : p(p), sz(sz), _z(_z), _visible(vis), _rotation(_rotation), spr_sys(spr_sys), tex(spr_sys.vtexture(name)), vb_pos(spr_sys.free_vb_pos()), my_place(spr_sys.attach(*this)), _use_rot_around(false)
{}

sge::sprite::sprite(const sprite& spr)
 : p(spr.p), sz(spr.sz), _z(spr._z), _visible(spr._visible), _rotation(spr._rotation), spr_sys(spr.spr_sys), tex(spr.tex), vb_pos(spr_sys.free_vb_pos()), my_place(spr_sys.attach(*this)), _use_rot_around(spr._use_rot_around), _rot_around(spr._rot_around)
{}

void sge::sprite::set_texture(const std::string& name)
{
	tex = spr_sys.vtexture(name);
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

sge::sprite::~sprite()
{
	spr_sys.detach(*this);
}

void sge::sprite::update()
{
	update_where(spr_sys.vb->begin()+vb_pos);
}

void sge::sprite::update_where(vertex_buffer::iterator it)
{
	const rect tex_rect = get_texture() ? tex_size_to_space_rect(tex->area(), get_texture()->width(), get_texture()->height()) : rect();
	if(rotation() == 0)
		fill_sprite_vertices(it, get_rect(), tex_rect);
	else
		fill_sprite_vertices_rotated(it, get_rect(), rotation(), _use_rot_around ? _rot_around : center(), tex_rect);
}

sge::index_buffer::iterator sge::sprite::update_ib(index_buffer::iterator it)
{
	fill_sprite_indices(it,vb_pos);
	return it;
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

