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
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/devicefuncs/get_depth_stencil_surface.hpp>
#include <sge/d3d9/surface/depth_stencil_onscreen.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <fcppt/optional/deref.hpp>


sge::d3d9::surface::depth_stencil_onscreen::depth_stencil_onscreen(
	IDirect3DDevice9 &_device
)
:
	sge::d3d9::resource(
		sge::d3d9::needs_reset::yes
	),
	device_(
		_device
	),
	surface_()
{
}

sge::d3d9::surface::depth_stencil_onscreen::~depth_stencil_onscreen()
{
}

sge::d3d9::surface::optional_d3d_ref
sge::d3d9::surface::depth_stencil_onscreen::surface() const
{
	return
		fcppt::optional::deref(
			surface_
		);
}

void
sge::d3d9::surface::depth_stencil_onscreen::init()
{
	surface_ =
		sge::d3d9::devicefuncs::get_depth_stencil_surface(
			device_
		);
}

void
sge::d3d9::surface::depth_stencil_onscreen::on_loss()
{
	surface_ =
		sge::d3d9::surface::optional_d3d_unique_ptr();
}

void
sge::d3d9::surface::depth_stencil_onscreen::on_reset()
{
	this->init();
}
