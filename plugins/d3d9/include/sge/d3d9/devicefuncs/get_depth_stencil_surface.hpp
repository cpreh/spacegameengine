//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_DEVICEFUNCS_GET_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_GET_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>

namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

sge::d3d9::surface::optional_d3d_unique_ptr get_depth_stencil_surface(IDirect3DDevice9 &);

}
}
}

#endif
