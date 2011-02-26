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


#include "../create_texture.hpp"
#include "../pool.hpp"
#include "../usage.hpp"
#include "../../convert/color_format.hpp"
#include <sge/renderer/texture/filter/need_mipmap.hpp>
#include <sge/renderere/texture/planar_parameters.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::d3d_texture_ptr const
sge::d3d9::texture::create_texture(
	d3d_device_ptr const _device,
	renderer::texture::planar_parameters const &_params
)
{
	IDirect3DTexture9 *ret = 0;

	if(
		_device->CreateTexture(
			static_cast<
				UINT
			>(
				_params.dim().w(),
			)
			static_cast<
				UINT
			>(
				_params.dim().h()
			),
			sge::renderer::texture::filter::need_mipmap(
				_params.filter().min()
			)
			?
				0
			:
				1,
			texture::usage(
				_params.resource_flags(),
				_params.capabilities()
			),
			d3d9::convert::color_format(
				_params.color_format()
			),
			texture::pool(
				_params.resource_flags(),
				_params.capabilities()
			),
			&ret,
			0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateTexture() failed!")
		);

	return
		d3d9::d3d_texture_ptr(
			ret
		);
}
