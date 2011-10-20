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


#include "../depth_stencil.hpp"
#include <fcppt/math/dim/basic_impl.hpp>

#if 0
sge::d3d9::texture::depth_stencil::depth_stencil(
	IDirect3DDevice9 *const _device,
	renderer::texture::depth_stencil_parameters const &_params
)
:
	texture::depth_stencil_basic(
		_device,
		_params
	)
{
}

sge::d3d9::texture::depth_stencil::~depth_stencil()
{
}

sge::d3d9::texture::depth_stencil::dim const
sge::d3d9::texture::depth_stencil::size() const
{
	return this->parameters().size();
}


sge::renderer::depth_stencil_surface_ptr const
sge::d3d9::texture::depth_stencil::surface() const
{
	return renderer::depth_stencil_surface_ptr();
}
#endif
