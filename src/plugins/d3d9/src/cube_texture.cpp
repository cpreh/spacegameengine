/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/stub.hpp>
#include <sge/renderer/scoped_lock.hpp>

sge::d3d9::cube_texture::cube_texture(renderer& r,
                                      const d3d_device_ptr device,
                                      const cube_side_array* const data,
                                      const size_type sz,
                                      const filter_args& filter_,
                                      const resource_flag_t flags)
:  detail::cube_texture_base_type(r, filter_, flags),
   device(device),
   sz(sz),
   lock_dest(0)
{
	do_reset();

	if(data)
		sge::cube_texture::set_data(*data);
}

IDirect3DBaseTexture9* sge::d3d9::cube_texture::do_reset()
{
	SGE_STUB_FUNCTION
	return 0;
}

void sge::d3d9::cube_texture::lock(const cube_side::type side, const lock_rect* const r)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::cube_texture::unlock()
{
	SGE_STUB_FUNCTION
}

sge::cube_texture::pointer sge::d3d9::cube_texture::data()
{
	return lock_dest;
}

sge::cube_texture::const_pointer sge::d3d9::cube_texture::data() const
{
	return lock_dest;
}

void sge::d3d9::cube_texture::set_data(const cube_side::type side,
                                       const const_pointer data)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::cube_texture::set_data(const cube_side::type side,
                                       const const_pointer data,
                                       const lock_rect& r)
{
	SGE_STUB_FUNCTION
}

sge::cube_texture::size_type sge::d3d9::cube_texture::border_size() const
{
	return sz;
}

sge::cube_texture::size_type sge::d3d9::cube_texture::size() const
{
	return border_size() * border_size();
}

void sge::d3d9::cube_texture::do_loss()
{
	tex.reset();
}
