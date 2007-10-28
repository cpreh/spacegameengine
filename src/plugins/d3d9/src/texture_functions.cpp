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


#include "../../../exception.hpp"
#include "../texture_functions.hpp"
#include "../conversion.hpp"

IDirect3DTexture9* sge::d3d9::create_texture(const d3d_device_ptr device,
                                             const texture::size_type width,
                                             const texture::size_type height,
                                             const filter_args& filter,
                                             const resource_flag_t flags,
                                             const bool system_mem)
{
	const DWORD usage = convert_cast<DWORD>(flags);
	const D3DPOOL pool = system_mem ? D3DPOOL_SYSTEMMEM : convert_cast<D3DPOOL>(flags);
	const D3DFORMAT format = D3DFMT_A8R8G8B8;

	IDirect3DTexture9* ptex = 0;
	if(device->CreateTexture(static_cast<UINT>(width),
	                         static_cast<UINT>(height),
	                         0, // FIXME
	                         usage,
	                         format,
	                         pool,
	                         &ptex,
	                         0
	) != D3D_OK)
		throw exception("CreateTexture() failed!");
	return ptex;
}

sge::texture::pointer sge::d3d9::lock_texture(const d3d_texture_ptr tex,
                                              const lock_rect* const rect,
                                              const resource_flag_t rflags)
{
	const DWORD lflags = convert_lock_flags(rflags, lock_flags::discard);

	D3DLOCKED_RECT lr;
	if(tex->LockRect(0, &lr, reinterpret_cast<const RECT*>(rect), lflags) != D3D_OK) // FIXME: reinterpret_cast is wrong here and may not work
		throw exception("LockRect() failed!");
	return static_cast<sge::texture::pointer>(lr.pBits);
}

void sge::d3d9::unlock_texture(const d3d_texture_ptr tex)
{
	if(tex->UnlockRect(0) != D3D_OK)
		throw exception("UnlockRect() failed!");
}

IDirect3DVolumeTexture9* sge::d3d9::create_volume_texture(const d3d_device_ptr device,
                                                          const texture::size_type width,
                                                          const texture::size_type height,
                                                          const texture::size_type depth,
                                                          const filter_args& filter,
                                                          const resource_flag_t flags,
                                                          const bool system_mem)
{
	const DWORD usage = convert_cast<DWORD>(flags);
	const D3DPOOL pool = system_mem ? D3DPOOL_SYSTEMMEM : convert_cast<D3DPOOL>(flags);
	const D3DFORMAT format = D3DFMT_A8R8G8B8;

	IDirect3DVolumeTexture9* ptex = 0;
	if(device->CreateVolumeTexture(static_cast<UINT>(width),
	                               static_cast<UINT>(height),
	                               static_cast<UINT>(depth),
	                               0, // FIXME
	                               usage,
	                               format,
	                               pool,
	                               &ptex,
	                               0
	) != D3D_OK)
		throw exception("CreateVolumeTexture() failed!");
	return ptex;
}

sge::volume_texture::pointer sge::d3d9::lock_volume_texture(const d3d_volume_texture_ptr tex,
                                                            const lock_box* const box,
                                                            const resource_flag_t rflags)
{
	const DWORD lflags = convert_lock_flags(rflags, lock_flags::discard);

	D3DLOCKED_BOX lb;
	if(tex->LockBox(0, &lb, reinterpret_cast<const D3DBOX*>(box), lflags) != D3D_OK) // FIXME: reinterpret_cast is wrong here and may not work
		throw exception("LockBox() failed!");
	return static_cast<sge::volume_texture::pointer>(lb.pBits);
}

void sge::d3d9::unlock_volume_texture(const d3d_volume_texture_ptr tex)
{
	if(tex->UnlockBox(0) != D3D_OK)
		throw exception("UnlockBox() failed!");
}

void sge::d3d9::update_texture(const d3d_device_ptr device,
                               IDirect3DBaseTexture9* const src,
                               IDirect3DBaseTexture9* const dest)
{
	if(device->UpdateTexture(src, dest) != D3D_OK)
		throw exception("UpdateTexture() failed!");

}
