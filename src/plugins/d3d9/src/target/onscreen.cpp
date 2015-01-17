/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/devicefuncs/set_depth_stencil_surface.hpp>
#include <sge/d3d9/devicefuncs/set_render_target.hpp>
#include <sge/d3d9/surface/color.hpp>
#include <sge/d3d9/surface/color_onscreen_target.hpp>
#include <sge/d3d9/surface/depth_stencil.hpp>
#include <sge/d3d9/surface/depth_stencil_onscreen_target.hpp>
#include <sge/d3d9/target/basic_impl.hpp>
#include <sge/d3d9/target/onscreen.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/color_buffer/surface_fwd.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::d3d9::target::onscreen::onscreen(
	IDirect3DDevice9 &_device,
	sge::image::color::format const _color_format,
	sge::renderer::target::viewport const &_viewport,
	sge::d3d9::resource_manager &_resources,
	sge::renderer::caps::target_surface_indices const _max_surfaces
)
:
	base(
		_device,
		_viewport,
		_max_surfaces
	),
	color_surface_(
		fcppt::make_unique_ptr<
			sge::d3d9::surface::color
		>(
			_device,
			_color_format,
			fcppt::make_unique_ptr<
				sge::d3d9::surface::color_onscreen_target
			>(
				_device
			)
		)
	),
	depth_stencil_surface_(
		fcppt::make_unique_ptr<
			sge::d3d9::surface::depth_stencil
		>(
			fcppt::make_unique_ptr<
				sge::d3d9::surface::depth_stencil_onscreen_target
			>(
				_device
			),
			sge::d3d9::needs_reset::yes
		)
	)
{
	_resources.add(
		*color_surface_
	);

	_resources.add(
		*depth_stencil_surface_
	);
}

sge::d3d9::target::onscreen::~onscreen()
{
}

sge::renderer::color_buffer::surface const &
sge::d3d9::target::onscreen::surface() const
{
	return *color_surface_;
}

bool
sge::d3d9::target::onscreen::needs_present() const
{
	return true;
}

void
sge::d3d9::target::onscreen::on_activate()
{
	sge::d3d9::devicefuncs::set_render_target(
		this->device(),
		sge::renderer::target::surface_index(
			0u
		),
		&color_surface_->surface()
	);

	sge::d3d9::devicefuncs::set_depth_stencil_surface(
		this->device(),
		&depth_stencil_surface_->surface()
	);
}

void
sge::d3d9::target::onscreen::on_deactivate()
{
	// Don't deactivate the 0th color surface because D3D9 doesn't allow it

	sge::d3d9::devicefuncs::set_depth_stencil_surface(
		this->device(),
		nullptr
	);
}

template
class
sge::d3d9::target::basic<
	sge::renderer::target::onscreen
>;
