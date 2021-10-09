//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <fcppt/assert/unreachable.hpp>

D3DFILLMODE
sge::d3d9::state::convert::fill_mode(sge::renderer::state::core::rasterizer::fill_mode const _type)
{
  switch (_type)
  {
  case sge::renderer::state::core::rasterizer::fill_mode::line:
    return D3DFILL_WIREFRAME;
  case sge::renderer::state::core::rasterizer::fill_mode::solid:
    return D3DFILL_SOLID;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
