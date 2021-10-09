//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surfacefuncs/get_desc.hpp>
#include <sge/d3d9/surfacefuncs/is_render_target.hpp>

bool sge::d3d9::surfacefuncs::is_render_target(IDirect3DSurface9 &_surface)
{
  return d3d9::surfacefuncs::get_desc(_surface).Usage & D3DUSAGE_RENDERTARGET;
}
