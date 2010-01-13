/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../target.hpp"
#include <sge/exception.hpp>
#include <sge/stub.hpp>

sge::d3d9::target::target(
	const d3d_device_ptr device,
	const dim_type& dim_)
:
	resource(),
	device(device),
	dim_(dim_)
{
	init();
}

void sge::d3d9::render_target::init()
{
	/*
	IDirect3DTexture9* t;
	if(device->CreateTexture(
		static_cast<UINT>(dim().w()),
		static_cast<UINT>(dim().h()),
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&t,
		0) != D3D_OK)
		throw exception(FCPPT_TEXT("Creating render target failed!"));
	tex.reset(t);
	IDirect3DSurface9* s;
	if(tex->GetSurfaceLevel(0,&s) != D3D_OK)
		throw exception(FCPPT_TEXT("Getting surface for render target failed!"));
	surface.reset(s);
	*/
}

void sge::d3d9::render_target::on_loss()
{
	surface.reset();
	tex.reset();
}

void sge::d3d9::render_target::on_reset()
{
	init();
}

sge::render_target::dim_type const
sge::d3d9::render_target::dim() const
{
	return dim_;
}
