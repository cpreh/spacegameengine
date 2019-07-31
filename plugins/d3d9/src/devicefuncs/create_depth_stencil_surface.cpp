//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
