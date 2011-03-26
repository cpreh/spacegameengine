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


#include "../create_cube.hpp"
#include "../mipmap_levels.hpp"
#include "../../convert/color_format.hpp"
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::texture::d3d_cube_texture_unique_ptr
sge::d3d9::texture::create_cube(
	IDirect3DDevice9 * const _device,
	renderer::texture::cube_parameters const &_params,
	D3DPOOL const _pool,
	d3d9::usage const _usage
)
{
	IDirect3DCubeTexture9 *ret = 0;

	if(
		_device->CreateCubeTexture(
			static_cast<
				UINT
			>(
				_params.size()
			),
			texture::mipmap_levels(
				_params.filter().min()
			),
			_usage.get(),
			d3d9::convert::color_format(
				_params.color_format()
			),
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
		texture::d3d_cube_texture_unique_ptr(
			ret
		);
}
