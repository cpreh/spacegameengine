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


#include "../depth_stencil_native.hpp"
#include "../../devicefuncs/create_depth_stencil_surface.hpp"
#include <fcppt/math/dim/basic_impl.hpp>

sge::d3d9::surface::depth_stencil_native::depth_stencil_native(
	IDirect3DDevice9 *const _device,
	sge::renderer::dim2 const &_dim,
	sge::renderer::depth_stencil_format::type const _format,
	D3DMULTISAMPLE_TYPE const _samples,
	d3d9::multi_sample_quality const _multi_sample_quality
)
:
	device_(_device),
	dim_(_dim),
	format_(_format),
	samples_(_samples),
	multi_sample_quality_(_multi_sample_quality)
{
}

sge::d3d9::surface::depth_stencil_native::~depth_stencil_native()
{
}

sge::d3d9::surface::d3d_unique_ptr
sge::d3d9::surface::depth_stencil_native::create() const
{
	return
		d3d9::devicefuncs::create_depth_stencil_surface(
			device_,
			dim_,
			format_,
			samples_,
			multi_sample_quality_
		);
}
