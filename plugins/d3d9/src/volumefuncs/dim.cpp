//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/volumefuncs/dim.hpp>
#include <sge/d3d9/volumefuncs/get_desc.hpp>
#include <sge/renderer/dim3.hpp>


sge::renderer::dim3 const
sge::d3d9::volumefuncs::dim(
	IDirect3DVolume9 &_surface
)
{
	D3DVOLUME_DESC const desc(
		sge::d3d9::volumefuncs::get_desc(
			_surface
		)
	);

	return
		sge::renderer::dim3(
			desc.Width,
			desc.Height,
			desc.Depth
		);
}
