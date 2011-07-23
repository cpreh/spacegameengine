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


#include "../create_offscreen_plain_surface.hpp"
#include "../../convert/color_format.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::d3d9::surface::d3d_unique_ptr
sge::d3d9::devicefuncs::create_offscreen_plain_surface(
	IDirect3DDevice9 *const _device,
	sge::renderer::dim2 const &_dim,
	sge::image::color::format::type const _format,
	D3DPOOL const _pool
)
{
	IDirect3DSurface9 *ret;

	if(
		_device->CreateOffscreenPlainSurface(
			static_cast<
				UINT
			>(
				_dim.w()
			),
			static_cast<
				UINT
			>(
				_dim.h()
			),
			d3d9::convert::color_format(
				_format
			),
			_pool,
			&ret,
			0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateOffscreenPlainSurface() failed!")
		);

	return
		d3d9::surface::d3d_unique_ptr(
			ret
		);
}
