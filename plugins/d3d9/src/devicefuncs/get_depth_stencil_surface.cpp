//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/get_depth_stencil_surface.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::d3d9::surface::optional_d3d_unique_ptr
sge::d3d9::devicefuncs::get_depth_stencil_surface(
	IDirect3DDevice9 &_device
)
{
	IDirect3DSurface9 *ret;

	switch(
		_device.GetDepthStencilSurface(
			&ret
		)
	)
	{
	case D3D_OK:
		return
			sge::d3d9::surface::optional_d3d_unique_ptr(
				sge::d3d9::surface::d3d_unique_ptr(
					ret
				)
			);
	case D3DERR_NOTFOUND:
		return
			sge::d3d9::surface::optional_d3d_unique_ptr();
	}

	throw
		sge::renderer::exception{
			FCPPT_TEXT("GetDepthStencilSurface() failed!")
		};
}
