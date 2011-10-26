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


#include <sge/d3d9/texture/create_planar.hpp>
#include <sge/d3d9/texture/mipmap/level_count.hpp>
#include <sge/d3d9/texture/mipmap/usage.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <fcppt/text.hpp>


sge::d3d9::texture::d3d_texture_unique_ptr
sge::d3d9::texture::create_planar(
	IDirect3DDevice9 * const _device,
	renderer::texture::planar_parameters const &_params,
	D3DFORMAT const _color_format,
	D3DPOOL const _pool,
	d3d9::usage const _usage
)
{
	IDirect3DTexture9 *ret = 0;

	if(
		_device->CreateTexture(
			static_cast<
				UINT
			>(
				_params.size().w()
			),
			static_cast<
				UINT
			>(
				_params.size().h()
			),
			texture::mipmap::level_count(
				_params.mipmap()
			),
			_usage.get()
			|
			texture::mipmap::usage(
				_params.mipmap()
			).get(),
			_color_format,
			_pool,
			&ret,
			0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateTexture() failed!")
		);

	return
		texture::d3d_texture_unique_ptr(
			ret
		);
}
