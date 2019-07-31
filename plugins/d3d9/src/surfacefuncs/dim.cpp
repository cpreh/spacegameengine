//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surfacefuncs/dim.hpp>
#include <sge/d3d9/surfacefuncs/get_desc.hpp>
#include <sge/renderer/dim2.hpp>


sge::renderer::dim2 const
sge::d3d9::surfacefuncs::dim(
	IDirect3DSurface9 &_surface
)
{
	D3DSURFACE_DESC const desc(
		sge::d3d9::surfacefuncs::get_desc(
			_surface
		)
	);

	return
		sge::renderer::dim2(
			desc.Width,
			desc.Height
		);
}
