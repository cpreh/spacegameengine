//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_DEVICEFUNCS_CREATE_OFFSCREEN_PLAIN_SURFACE_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_CREATE_OFFSCREEN_PLAIN_SURFACE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/renderer/dim2_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

d3d9::surface::d3d_unique_ptr create_offscreen_plain_surface(
    IDirect3DDevice9 &, sge::renderer::dim2 const &, sge::image::color::format, D3DPOOL);

}
}
}

#endif
