/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/cube_side.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/texturefuncs/get_cube_map_surface.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>


sge::d3d9::surface::d3d_unique_ptr
sge::d3d9::texturefuncs::get_cube_map_surface(
	IDirect3DCubeTexture9 &_texture,
	sge::renderer::texture::cube_side const _side,
	sge::renderer::texture::mipmap::level const _level
)
{
	IDirect3DSurface9 *result;

	if(
		_texture.GetCubeMapSurface(
			sge::d3d9::convert::cube_side(
				_side
			),
			_level.get(),
			&result
		)
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("GetCubeMapSurface failed!")
		);

	return
		sge::d3d9::surface::d3d_unique_ptr(
			result
		);
}
