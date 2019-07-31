//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surfacefuncs/dim.hpp>
#include <sge/d3d9/texture/buffer_size.hpp>
#include <sge/d3d9/volumefuncs/dim.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/dim3.hpp>


sge::renderer::dim2 const
sge::d3d9::texture::buffer_size(
	IDirect3DSurface9 &_surface
)
{
	return
		sge::d3d9::surfacefuncs::dim(
			_surface
		);
}

sge::renderer::dim3 const
sge::d3d9::texture::buffer_size(
	IDirect3DVolume9 &_volume
)
{
	return
		sge::d3d9::volumefuncs::dim(
			_volume
		);
}
