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
#include <sge/d3d9/multi_sample_quality.hpp>
#include <sge/d3d9/devicefuncs/create_depth_stencil_surface.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/surface/depth_stencil_native.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>


sge::d3d9::surface::depth_stencil_native::depth_stencil_native(
	IDirect3DDevice9 &_device,
	sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters,
	D3DMULTISAMPLE_TYPE const _samples,
	sge::d3d9::multi_sample_quality const _multi_sample_quality
)
:
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
	)
{
}

sge::d3d9::surface::depth_stencil_native::~depth_stencil_native()
{
}

sge::d3d9::surface::d3d_unique_ptr
sge::d3d9::surface::depth_stencil_native::create() const
{
	return
		sge::d3d9::devicefuncs::create_depth_stencil_surface(
			device_,
			parameters_,
			samples_,
			multi_sample_quality_
		);
}
