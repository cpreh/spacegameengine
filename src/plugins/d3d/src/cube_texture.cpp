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


#include "../cube_texture.hpp"
#include "../../../renderer/lock_ptr.hpp"
#include "../../../algorithm.hpp"

#include <iostream>

sge::d3d::cube_texture::cube_texture(renderer* const r, d3d_device_ptr device, const cube_side_array* data, const size_type sz, const resource_flag_t nflags)
:  d3d::texture_base(0),
   resource(r, nflags & RF_Dynamic),
   device(device), _flags(nflags), sz(sz), lock_dest(0)
{
	init(data);
}

void sge::d3d::cube_texture::init(const cube_side_array* const src)
{
	/*if(!src)
		return;
	const cube_side_array& data = *src;
	for(cube_side_array::size_type s = 0; s < data.size(); ++s)
	{
		lock_ptr<cube_texture*> l(this,cube_side(s));
		copy(data[s],data[s]+size(),lock_dest);
	}*/
}

void sge::d3d::cube_texture::lock(const cube_side side, const lock_rect* const r)
{
	std::cerr << "stub: d3d::cube_texture::lock\n";
}

void sge::d3d::cube_texture::unlock()
{
	std::cerr << "stub: d3d::cube_texture::unlock\n";
}

void sge::d3d::cube_texture::set_data(const cube_side side, const const_pointer data, const lock_rect* const r)
{
	std::cerr << "stub: d3d::cube_texture::set_data";
}

sge::resource_flag_t sge::d3d::cube_texture::flags() const
{
	return _flags;
}

sge::cube_texture::size_type sge::d3d::cube_texture::size() const
{
	return sz;
}

void sge::d3d::cube_texture::on_loss()
{
	tex.reset();
}

void sge::d3d::cube_texture::on_reset()
{
	init();
}
