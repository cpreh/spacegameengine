/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../texture_functions.hpp"
#if 0
#include "../conversion.hpp"
#include <sge/exception.hpp>

IDirect3DVolumeTexture9* sge::d3d9::create_volume_texture(
	const d3d_device_ptr device,
	const volume_texture::box_type& box,
	const filter_args& filter,
	const resource_flag_t flags,
	const bool system_mem)
{
	const DWORD usage = convert_cast<DWORD>(flags);
	const D3DPOOL pool = system_mem ? D3DPOOL_SYSTEMMEM : convert_cast<D3DPOOL>(flags);
	const D3DFORMAT format = D3DFMT_A8R8G8B8;

	IDirect3DVolumeTexture9* ptex = 0;
	if(device->CreateVolumeTexture(
		static_cast<UINT>(box.w()),
		static_cast<UINT>(box.h()),
		static_cast<UINT>(box.d()),
		0, // FIXME
		usage,
		format,
		pool,
		&ptex,
		0
	) != D3D_OK)
		throw exception(FCPPT_TEXT("CreateVolumeTexture() failed!"));
	return ptex;
}

sge::volume_texture::pointer
sge::d3d9::lock_volume_texture(
	const d3d_volume_texture_ptr tex,
	const lock_box* const box,
	const lock_flag_t lflags,
	const resource_flag_t rflags)
{
	const DWORD flags = convert_lock_flags(lflags, rflags);

	D3DLOCKED_BOX lb;
	if(tex->LockBox(0, &lb, reinterpret_cast<const D3DBOX*>(box), flags) != D3D_OK) // FIXME: reinterpret_cast is wrong here and may not work
		throw exception(FCPPT_TEXT("LockBox() failed!"));
	return static_cast<sge::volume_texture::pointer>(lb.pBits);
}

void sge::d3d9::unlock_volume_texture(const d3d_volume_texture_ptr tex)
{
	if(tex->UnlockBox(0) != D3D_OK)
		throw exception(FCPPT_TEXT("UnlockBox() failed!"));
}
#endif
