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
#include "../devicefuncs/set_depth_stencil_surface.hpp"
#include "../devicefuncs/set_render_target.hpp"
#include "../surface/color_ptr.hpp"
#include "../surface/color.hpp"
#include "../surface/depth_stencil.hpp"
#include <sge/renderer/surface_index.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/container/index_map_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::d3d9::offscreen_target::offscreen_target(
	IDirect3DDevice9 *const _device
)
:
	base(
		_device,
		sge::renderer::viewport(
			sge::renderer::pixel_rect::null()
		)
	)
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
	color_surfaces_[
		_index.get()
	] =
		fcppt::dynamic_pointer_cast<
			d3d9::surface::color
		>(
			_surface
		);
}

void
sge::d3d9::offscreen_target::depth_stencil_surface(
	renderer::depth_stencil_surface_ptr const _surface
)
{
	depth_stencil_surface_ =
		fcppt::dynamic_pointer_cast<
			d3d9::surface::depth_stencil
		>(
			_surface
		);
}

sge::renderer::optional_dim2 const
sge::d3d9::offscreen_target::size() const
{
	return renderer::optional_dim2();
}

void
sge::d3d9::offscreen_target::on_activate()
{
	this->change_surfaces(
		true
	);
}

void
sge::d3d9::offscreen_target::on_deactivate()
{
	this->change_surfaces(
		false
	);
}

void
sge::d3d9::offscreen_target::change_surfaces(
	bool const _activate
)
{
	for(
		color_surface_map::size_type index(
			0u
		);
		index != color_surfaces_.size();
		++index
	)
	{
		d3d9::surface::color_ptr const surface(
			color_surfaces_[
				index
			]
		);

		if(
			surface
		)
			devicefuncs::set_render_target(
				this->device(),
				renderer::surface_index(
					static_cast<
						renderer::surface_index::value_type
					>(
						index
					)
				),
				_activate
				?
					surface->surface()
				:
					0
			);
	}

	if(
		depth_stencil_surface_
	)
		devicefuncs::set_depth_stencil_surface(
			this->device(),
			_activate
			?
				depth_stencil_surface_->surface()
			:
				0
		);
}

template class
sge::d3d9::basic_target<
	sge::renderer::target
>;
