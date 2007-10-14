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

sge::d3d::texture::texture(renderer* const r,
                           const d3d_device_ptr device,
                           const const_pointer data,
                           const size_type _width,
                           const size_type _height,
                           const filter_args& filter,
                           const resource_flag_t nflags)
: d3d::texture_base(0),
  resource(r, nflags & resource_flags::dynamic),
  device(device),
  _flags(nflags),
  _width(_width),
  _height(_height),
  filter(filter),
  lock_dest(0)
{
	init();
	if(data)
		set_data(data);
}

void sge::d3d::texture::init()
{
	const DWORD usage = convert_cast<DWORD>(flags());
	const D3DPOOL pool = convert_cast<D3DPOOL>(flags());
	const D3DFORMAT format = D3DFMT_A8R8G8B8;

	IDirect3DTexture9* ptex;
	if(device->CreateTexture(static_cast<UINT>(width()),static_cast<UINT>(height()),0,usage,format,pool,&ptex,0) != D3D_OK)
		throw exception("failed to create texture");
	tex.reset(ptex);
	set_base(tex.get());
}

void sge::d3d::texture::lock(const lock_rect* const r)
{
	const lock_flag_t _lflags = lock_flags::discard;
	const DWORD lflags = convert_lock_flags(_lflags, flags());
	if(flags() & resource_flags::dynamic)
	{
		D3DLOCKED_RECT lr;
		if(tex->LockRect(0,&lr,reinterpret_cast<const RECT*>(r),lflags) != D3D_OK)
			throw exception("lock texture failed");
		lock_dest = static_cast<pointer>(lr.pBits);
	}
	else
	{
		IDirect3DTexture9* temp;
		if(device->CreateTexture(static_cast<UINT>(width()),static_cast<UINT>(height()),1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&temp,0) != D3D_OK)
			throw exception("creating temp texture failed");
		temp_tex.reset(temp);
		D3DLOCKED_RECT lr;
		if(temp_tex->LockRect(0,&lr,0,lflags) != D3D_OK)
			throw exception("lock texture failed");
		lock_dest = static_cast<pointer>(lr.pBits);
	}
}

void sge::d3d::texture::unlock()
{
	if(flags() & resource_flags::dynamic)
	{
		if(tex->UnlockRect(0) != D3D_OK)
			throw exception("unlock texture failed");
	}
	else
	{
		if(temp_tex->UnlockRect(0) != D3D_OK)
			throw exception("unlock texture failed");
		if(device->UpdateTexture(temp_tex.get(),temp_tex.get()) != D3D_OK)
			throw exception("update texture failed");
		temp_tex.reset();
	}
	lock_dest = 0;
}

void sge::d3d::texture::on_loss()
{
	tex.reset();
}

void sge::d3d::texture::on_reset()
{
	init();
}

void sge::d3d::texture::set_data(const const_pointer data)
{
	const scoped_lock<texture*> l(this);
	std::copy(data, data + size(), lock_dest);
}

void sge::d3d::texture::set_data(const const_pointer data, const lock_rect& r)
{
	const scoped_lock<texture*> l(this, r);
	std::copy(data, data + r.w() * r.h(), lock_dest);
}

sge::d3d::texture::size_type sge::d3d::texture::width() const
{
	return _width;
}

sge::d3d::texture::size_type sge::d3d::texture::height() const
{
	return _height;
}

sge::d3d::texture::size_type sge::d3d::texture::size() const
{
	return width()*height();
}

sge::resource_flag_t sge::d3d::texture::flags() const
{
	return _flags;
}
