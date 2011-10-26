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


#include <sge/d3d9/surface/color_holder.hpp>
#include <sge/d3d9/surfacefuncs/color_format.hpp>
#include <sge/d3d9/surfacefuncs/dim.hpp>
#include <sge/d3d9/surfacefuncs/is_render_target.hpp>
#include <fcppt/move.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::d3d9::surface::color_holder::color_holder(
	surface::d3d_unique_ptr _surface
)
:
	surface_(
		fcppt::move(
			_surface
		)
	),
	size_(
		surfacefuncs::dim(
			surface_.get()
		)
	),
	format_(
		surfacefuncs::color_format(
			surface_.get()
		)
	),
	is_render_target_(
		surfacefuncs::is_render_target(
			surface_.get()
		)
	)
{
}

sge::d3d9::surface::color_holder::~color_holder()
{
}

IDirect3DSurface9 *
sge::d3d9::surface::color_holder::get() const
{
	return surface_.get();
}

sge::renderer::dim2 const &
sge::d3d9::surface::color_holder::size() const
{
	return size_;
}

sge::image::color::format::type
sge::d3d9::surface::color_holder::format() const
{
	return format_;
}

bool
sge::d3d9::surface::color_holder::is_render_target() const
{
	return is_render_target_;
}
