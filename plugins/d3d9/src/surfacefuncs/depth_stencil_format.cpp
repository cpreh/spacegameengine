//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_depth_stencil_format.hpp>
#include <sge/d3d9/surfacefuncs/depth_stencil_format.hpp>
#include <sge/d3d9/surfacefuncs/get_desc.hpp>
#include <sge/image/ds/format.hpp>

sge::image::ds::format sge::d3d9::surfacefuncs::depth_stencil_format(IDirect3DSurface9 &_surface)
{
  return sge::d3d9::convert::to_depth_stencil_format(
      sge::d3d9::surfacefuncs::get_desc(_surface).Format);
}
