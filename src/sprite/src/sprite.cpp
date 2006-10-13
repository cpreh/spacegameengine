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

sge::sprite::sprite(sprite_system& s, const point p, const dim sz, const unsigned _z, const std::string& name, const bool vis)
	: p(p), sz(sz), _z(_z), _rot(0), _use_rot_around(false), _visible(vis), s(s), tex(s.vtexture(name)), vb_pos(s.free_vb_pos()), my_place(s.attach(*this))
{}

sge::sprite::sprite(const sprite& spr)
	: p(spr.p), sz(spr.sz), _z(spr._z), _rot(spr._rot), _rot_around(spr._rot_around), _use_rot_around(spr._use_rot_around), s(spr.s), tex(spr.tex), vb_pos(s.free_vb_pos()), my_place(s.attach(*this))
{}

void sge::sprite::set_texture(const std::string& name) { tex = s.vtexture(name); }

sge::sprite::~sprite() { s.detach(*this); }

void sge::sprite::update()
{
	update_where(s.vb->begin()+vb_pos);
}

void sge::sprite::update_where(vertex_buffer::iterator it)
{
	const rect tex_rect = get_texture() ? tex_size_to_space_rect(tex->area(), get_texture()->width(), get_texture()->height()) : rect();
	if(_rot == 0)
		fill_sprite_vertices(it, get_rect(), tex_rect);
	else
		fill_sprite_vertices_rotated(it, get_rect(), _rot, _use_rot_around ? _rot_around : center(), tex_rect);
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
	update_where(s.vb->create_iterator(buf.c_array()));
	s.vb->set_data(buf.data(),vb_pos,4);
	
	{
	boost::array<index_buffer::value_type, detail::indices_per_sprite> buf;
	update_ib(buf.c_array());
	s.ib->set_data(buf.data(), 0, detail::indices_per_sprite);
	}

	s.set_parameters();
	s.r->set_texture(0,get_texture());
	s.r->render(s.vb,s.ib,0,4,PT_Triangle,2);
}

sge::texture_ptr sge::sprite::get_texture() const
{
	return tex ? tex->my_texture() : texture_ptr();
}

sge::point sge::sprite::center() const
{
	return point(x() + width() / 2, y() + height() / 2);
}

void sge::sprite::rotate_acc(const space_unit r)
{
	_rot += r;
	if(_rot > 2*PI)
		_rot -= 2*PI;
	if(_rot < 0)
		_rot += 2*PI;
}

void sge::sprite::rotate_around(const point* const p)
{
	_use_rot_around = p;
	if(p)
		_rot_around = *p;
}

bool sge::sprite::equal_texture(const sprite& l, const sprite& r)
{
	return l.get_texture() == r.get_texture();
}

bool sge::sprite::less(const sprite& l, const sprite& r)
{
	const bool lvis = l.visible(), rvis = r.visible();
	const unsigned lz = l.z(), rz = r.z();
	sge::texture_ptr ltex = l.get_texture(), rtex = r.get_texture();

	return lvis == rvis ?
	                    lz == rz ?
	                             ltex == rtex ? 
	                                          false
	                                          : ltex < rtex
		                     : lz < rz
		            : lvis < rvis;
}

