//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/parameters/convert/depth_stencil_buffer.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <fcppt/assert/unreachable.hpp>

D3DFORMAT
sge::d3d9::parameters::convert::depth_stencil_buffer(
    sge::renderer::pixel_format::depth_stencil const _type)
{
  switch (_type)
  {
  case sge::renderer::pixel_format::depth_stencil::off:
    return D3DFMT_UNKNOWN;
  case sge::renderer::pixel_format::depth_stencil::d16:
    return D3DFMT_D16;
  case sge::renderer::pixel_format::depth_stencil::d24:
    return D3DFMT_D24X8;
  case sge::renderer::pixel_format::depth_stencil::d32:
    return D3DFMT_D32;
  case sge::renderer::pixel_format::depth_stencil::d24s8:
    return D3DFMT_D24S8;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
