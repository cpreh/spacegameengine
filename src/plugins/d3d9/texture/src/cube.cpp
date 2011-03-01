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


#include "../cube.hpp"

sge::d3d9::texture::cube::cube(
	IDirect3DDevice9 *const _device,
	renderer::texture::cube_parameters const &_params
)
:
	texture::cube_basic(
		_device,
		_params
	)
{
}

sge::d3d9::texture::cube::~cube()
{
}

sge::image2d::view::object const
sge::d3d9::texture::cube::lock(
	renderer::texture::cube_side::type,
	renderer::lock_rect const &,
	renderer::lock_mode::type
)
{
}

sge::image2d::view::const_object const
sge::d3d9::texture::cube::lock(
	renderer::texture::cube_side::type,
	renderer::lock_rect const &
) const
{
}

void
sge::d3d9::texture::cube::unlock() const
{
}

sge::d3d9::texture::cube::size_type
sge::d3d9::texture::cube::border_size() const
{
}

IDirect3DBaseTexture9 *
sge::d3d9::texture::cube::do_reset()
{
	return 0;
}
