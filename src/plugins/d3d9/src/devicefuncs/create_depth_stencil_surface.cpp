/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/convert/depth_stencil_format.hpp>
#include <sge/d3d9/devicefuncs/create_depth_stencil_surface.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>
#include <fcppt/text.hpp>


sge::d3d9::surface::d3d_unique_ptr
sge::d3d9::devicefuncs::create_depth_stencil_surface(
	IDirect3DDevice9 &_device,
	sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters,
	D3DMULTISAMPLE_TYPE const _samples,
	sge::d3d9::multi_sample_quality const _multi_sample_quality
)
{
	IDirect3DSurface9 *ret;

	if(
		_device.CreateDepthStencilSurface(
			static_cast<
				UINT
			>(
				_parameters.size().w()
			),
			static_cast<
				UINT
			>(
				_parameters.size().h()
			),
			sge::d3d9::convert::depth_stencil_format(
				_parameters.format()
			),
			_samples,
			_multi_sample_quality.get(),
			TRUE, // discard
			&ret,
			0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateDepthStencilSurface() failed!")
		);

	return
		sge::d3d9::surface::d3d_unique_ptr(
			ret
		);
}
