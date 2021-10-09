//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/dest_blend_func.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <fcppt/assert/unreachable.hpp>

D3DBLEND
sge::d3d9::state::convert::dest_blend_func(sge::renderer::state::core::blend::dest const _type)
{
  switch (_type)
  {
  case sge::renderer::state::core::blend::dest::zero:
    return D3DBLEND_ZERO;
  case sge::renderer::state::core::blend::dest::one:
    return D3DBLEND_ONE;
  case sge::renderer::state::core::blend::dest::src_color:
    return D3DBLEND_SRCCOLOR;
  case sge::renderer::state::core::blend::dest::inv_src_color:
    return D3DBLEND_INVSRCCOLOR;
  case sge::renderer::state::core::blend::dest::src_alpha:
    return D3DBLEND_SRCALPHA;
  case sge::renderer::state::core::blend::dest::inv_src_alpha:
    return D3DBLEND_INVSRCALPHA;
  case sge::renderer::state::core::blend::dest::dest_alpha:
    return D3DBLEND_DESTALPHA;
  case sge::renderer::state::core::blend::dest::inv_dest_alpha:
    return D3DBLEND_INVDESTALPHA;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
