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


#include "../offscreen_target.hpp"
#include "../basic_target_impl.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>

sge::d3d9::offscreen_target::offscreen_target(
	IDirect3DDevice9 *const _device
)
:
	base(
		_device,
		// TODO:
		sge::renderer::viewport(
			sge::renderer::pixel_rect::null()
		)
	),
	d3d9::resource(
		D3DPOOL_DEFAULT
	),
	device_(_device)
{
}

sge::d3d9::offscreen_target::~offscreen_target()
{
}

void
sge::d3d9::offscreen_target::color_surface(
	renderer::color_surface_ptr const _surface,
	renderer::surface_index const _index
)
{
}

void
sge::d3d9::offscreen_target::depth_stencil_surface(
	renderer::depth_stencil_surface_ptr const _surface
)
{
}

sge::renderer::optional_dim2 const
sge::d3d9::offscreen_target::dim() const
{
	return renderer::optional_dim2();
}

#if 0
void
sge::d3d9::render_target::init()
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
#endif

void
sge::d3d9::offscreen_target::on_loss()
{
#if 0
	surface.reset();

	tex.reset();
#endif
}

void
sge::d3d9::offscreen_target::on_reset()
{
#if 0
	init();
#endif
}

template class
sge::d3d9::basic_target<
	sge::renderer::target
>;
