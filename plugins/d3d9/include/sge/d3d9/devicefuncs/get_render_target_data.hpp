//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_DEVICEFUNCS_GET_RENDER_TARGET_DATA_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_GET_RENDER_TARGET_DATA_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>

namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

void get_render_target_data(IDirect3DDevice9 &, IDirect3DSurface9 &source, IDirect3DSurface9 &dest);

}
}
}

#endif
