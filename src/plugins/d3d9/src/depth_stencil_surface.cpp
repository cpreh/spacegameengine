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


#include "../depth_stencil_surface.hpp"
#include "../surfacefuncs/dim.hpp"
#include "../surfacefuncs/depth_stencil_format.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/move.hpp>

sge::d3d9::depth_stencil_surface::depth_stencil_surface(
	d3d9::d3d_surface_unique_ptr _surface
)
:
	surface_(
		fcppt::move(
			_surface
		)
	)
{
}

sge::d3d9::depth_stencil_surface::~depth_stencil_surface()
{
}

sge::d3d9::depth_stencil_surface::dim const
sge::d3d9::depth_stencil_surface::size() const
{
	return
		d3d9::surfacefuncs::dim(
			surface_.get()
		);
}

sge::renderer::depth_stencil_format::type
sge::d3d9::depth_stencil_surface::format() const
{
	return
		d3d9::surfacefuncs::depth_stencil_format(
			surface_.get()
		);
}

IDirect3DSurface9 *
sge::d3d9::depth_stencil_surface::surface() const
{
	return surface_.get();
}
