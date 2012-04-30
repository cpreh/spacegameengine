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
#include <sge/renderer/color_surface_fwd.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/null_ptr.hpp>


namespace
{

void
set_surfaces(
	IDirect3DDevice9 *,
	IDirect3DSurface9 *color,
	IDirect3DSurface9 *depth_stencil
);

}

sge::d3d9::target::onscreen::onscreen(
	IDirect3DDevice9 *const _device,
	sge::renderer::target::viewport const &_viewport,
	sge::d3d9::resource_manager &_resources
)
:
	base(
		_device,
		_viewport
	),
	color_surface_(
		fcppt::make_unique_ptr<
			sge::d3d9::surface::color
		>(
			_device,
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
			d3d9::needs_reset::yes
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

sge::renderer::color_surface const &
sge::d3d9::target::onscreen::surface() const
{
	return *color_surface_;
}

void
sge::d3d9::target::onscreen::on_activate()
{
	::set_surfaces(
		this->device(),
		color_surface_->surface(),
		depth_stencil_surface_->surface()
	);
}

void
sge::d3d9::target::onscreen::on_deactivate()
{
	::set_surfaces(
		this->device(),
		fcppt::null_ptr(),
		fcppt::null_ptr()
	);
}

template
class
sge::d3d9::target::basic<
	sge::renderer::target::onscreen
>;

namespace
{

void
set_surfaces(
	IDirect3DDevice9 *const _device,
	IDirect3DSurface9 *const _color,
	IDirect3DSurface9 *const _depth_stencil
)
{
	sge::d3d9::devicefuncs::set_render_target(
		_device,
		sge::renderer::target::surface_index(
			0u
		),
		_color
	);

	sge::d3d9::devicefuncs::set_depth_stencil_surface(
		_device,
		_depth_stencil
	);
}

}
