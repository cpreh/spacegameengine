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
#include <sge/d3d9/multi_sample_quality.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/devicefuncs/create_depth_stencil_surface.hpp>
#include <sge/d3d9/surface/depth_stencil_offscreen.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <sge/d3d9/surfacefuncs/depth_stencil_format.hpp>
#include <sge/d3d9/surfacefuncs/dim.hpp>
#include <sge/image/ds/format.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/object.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/unimplemented_message.hpp>


sge::d3d9::surface::depth_stencil_offscreen::depth_stencil_offscreen(
	IDirect3DDevice9 &_device,
	sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters,
	D3DMULTISAMPLE_TYPE const _samples,
	sge::d3d9::multi_sample_quality const _multi_sample_quality
)
:
	sge::renderer::depth_stencil_buffer::surface(),
	sge::d3d9::resource(
		sge::d3d9::needs_reset::yes
	),
	device_(
		_device
	),
	parameters_(
		_parameters
	),
	samples_(
		_samples
	),
	multi_sample_quality_(
		_multi_sample_quality
	),
	surface_()
{
	this->init();
}

sge::d3d9::surface::depth_stencil_offscreen::~depth_stencil_offscreen()
{
}

sge::d3d9::surface::depth_stencil_offscreen::dim const
sge::d3d9::surface::depth_stencil_offscreen::size() const
{
	return
		sge::d3d9::surfacefuncs::dim(
			this->surface()
		);
}

sge::image::ds::format
sge::d3d9::surface::depth_stencil_offscreen::format() const
{
	return
		sge::d3d9::surfacefuncs::depth_stencil_format(
			this->surface()
		);
}

IDirect3DSurface9 &
sge::d3d9::surface::depth_stencil_offscreen::surface() const
{
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			surface_
		);
}

sge::d3d9::surface::depth_stencil_offscreen::const_view const
sge::d3d9::surface::depth_stencil_offscreen::lock(
	lock_area const &
) const
{
	// TODO: Why?
	throw
		sge::renderer::exception(
			FCPPT_TEXT("depth stencil surfaces can't be locked")
		);
}

sge::d3d9::surface::depth_stencil_offscreen::view const
sge::d3d9::surface::depth_stencil_offscreen::lock(
	lock_area const &,
	sge::renderer::lock_mode
)
{
	throw
		sge::renderer::exception(
			FCPPT_TEXT("depth stencil surfaces can't be locked")
		);
}

void
sge::d3d9::surface::depth_stencil_offscreen::unlock() const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("depth stencil surfaces can't be unlocked")
	);
}

void
sge::d3d9::surface::depth_stencil_offscreen::init()
{
	surface_ =
		sge::d3d9::surface::optional_d3d_unique_ptr{
			sge::d3d9::devicefuncs::create_depth_stencil_surface(
				device_,
				parameters_,
				samples_,
				multi_sample_quality_
			)
		};
}

void
sge::d3d9::surface::depth_stencil_offscreen::on_loss()
{
	surface_ =
		sge::d3d9::surface::optional_d3d_unique_ptr();
}

void
sge::d3d9::surface::depth_stencil_offscreen::on_reset()
{
	this->init();
}
