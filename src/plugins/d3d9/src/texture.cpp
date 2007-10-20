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


#include <algorithm>
#include "../../../renderer/scoped_lock.hpp"
#include "../../../exception.hpp"
#include "../texture.hpp"
#include "../conversion.hpp"

sge::d3d9::texture::texture(renderer& r,
                            const d3d_device_ptr device,
                            const const_pointer data,
                            const size_type _width,
                            const size_type _height,
                            const filter_args& filter,
                            const resource_flag_t nflags)
: basic_texture(r, filter, nflags)
  device(device),
  _width(_width),
  _height(_height),
  lock_dest(0)
{
	reset();
	if(data)
		set_data(data);
}

IDirect3DBaseTexture9* sge::d3d9::texture::on_reset()
{
	tex.reset(create_texture(device, width(), height(), filter(), flags()));
	return tex.get();
}

void sge::d3d9::texture::on_loss()
{
	tex.reset();
}

void sge::d3d9::texture::lock()
{
	lock(0);
}

void sge::d3d9::texture::lock(const lock_rect& r)
{
	lock(&r);
}

void sge::d3d9::texture::lock(const lock_rect* const r)
{
	if(flags() & resource_flags::dynamic)
		lock_dest = lock_texture(tex, r);
	else
	{
		temp_tex.reset(create_texture(device, width(), height(), filter(), flags()));
		lock_dest = lock_texture(temp_tex, r);
//		if(device->CreateTexture(static_cast<UINT>(width()),static_cast<UINT>(height()),1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&temp,0) != D3D_OK)
//			throw exception("creating temp texture failed");
	}
}

void sge::d3d9::texture::unlock()
{
	if(flags() & resource_flags::dynamic)
		unlock_texture(tex);
	/*{
		if(tex->UnlockRect(0) != D3D_OK)
			throw exception("unlock texture failed");
	}*/
	else
	{
		unlock_texture(temp_tex);
		//if(temp_tex->UnlockRect(0) != D3D_OK)
		//	throw exception("unlock texture failed");
		if(device->UpdateTexture(temp_tex.get(), tex.get()) != D3D_OK)
			throw exception("UpdateTexture() failed!");
		temp_tex.reset();
	}
	lock_dest = 0;
}

void sge::d3d9::texture::set_data(const const_pointer data)
{
	const scoped_lock<texture*> l(this);
	std::copy(data, data + size(), lock_dest);
}

void sge::d3d9::texture::set_data(const const_pointer data, const lock_rect& r)
{
	const scoped_lock<texture*> l(this, r);
	std::copy(data, data + r.w() * r.h(), lock_dest);
}

sge::d3d9::texture::size_type sge::d3d::texture::width() const
{
	return _width;
}

sge::d3d9::texture::size_type sge::d3d::texture::height() const
{
	return _height;
}

sge::d3d9::texture::size_type sge::d3d::texture::size() const
{
	return width() * height();
}
