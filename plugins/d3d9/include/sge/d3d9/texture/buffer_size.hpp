//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_BUFFER_SIZE_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BUFFER_SIZE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/dim3_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

sge::renderer::dim2 const
buffer_size(
	IDirect3DSurface9 &
);

sge::renderer::dim3 const
buffer_size(
	IDirect3DVolume9 &
);

}
}
}

#endif
