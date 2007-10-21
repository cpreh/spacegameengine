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


#include "../../../renderer/scoped_lock.hpp"
#include "../../../exception.hpp"
#include "../volume_texture.hpp"
#include "../conversion.hpp"
#include "../texture_functions.hpp"

sge::d3d9::volume_texture::volume_texture(renderer& r,
                                          const d3d_device_ptr device,
                                          const const_pointer src,
                                          const size_type _width,
                                          const size_type _height,
                                          const size_type _depth,
                                          const filter_args& filter,
                                          const resource_flag_t flags)
: detail::volume_texture_base_type(r, filter, flags),
  device(device),
  lock_dest(0),
  _width(_width),
  _height(_height),
  _depth(_depth)
{
	on_reset();
	if(src)
		set_data(src);
}

IDirect3DBaseTexture9* sge::d3d9::volume_texture::do_reset()
{
	tex.reset(create_volume_texture(device, width(), height(), depth(), filter(), flags(), false));
	return tex.get();
}

void sge::d3d9::volume_texture::lock()
{
	lock(0);
}

void sge::d3d9::volume_texture::lock(const lock_box& b)
{
	lock(&b);
}

void sge::d3d9::volume_texture::lock(const lock_box* const b)
{
	if(flags() & resource_flags::dynamic)
		lock_dest = lock_volume_texture(tex, b, flags());
	else
	{
		temp_tex.reset(create_volume_texture(device, width(), height(), depth(), filter(), flags(), true));
		lock_dest = lock_volume_texture(tex, b, flags());
	}
}

void sge::d3d9::volume_texture::unlock()
{
	if(flags() & resource_flags::dynamic)
		unlock_volume_texture(tex);
	else
	{
		unlock_volume_texture(temp_tex);
		update_texture(device, temp_tex.get(), tex.get());
		temp_tex.reset();
	}
	lock_dest = 0;
}

void sge::d3d9::volume_texture::do_loss()
{
	tex.reset();
}

void sge::d3d9::volume_texture::set_data(const const_pointer data)
{
	scoped_lock<volume_texture*> l(this);
	std::copy(data, data + size(), lock_dest);
}

void sge::d3d9::volume_texture::set_data(const const_pointer data, const lock_box& b)
{
	scoped_lock<volume_texture*> l(this, b);
	std::copy(data, data + b.size(),lock_dest);
}

sge::d3d9::volume_texture::size_type sge::d3d9::volume_texture::width() const
{
	return _width;
}

sge::d3d9::volume_texture::size_type sge::d3d9::volume_texture::height() const
{
	return _height;
}

sge::d3d9::volume_texture::size_type sge::d3d9::volume_texture::depth() const
{
	return _depth;
}

sge::d3d9::volume_texture::size_type sge::d3d9::volume_texture::size() const
{
	return width() * height() * depth();
}
