//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/stencil_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/op.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

D3DSTENCILOP
sge::d3d9::state::convert::stencil_op(
    sge::renderer::state::core::depth_stencil::stencil::op const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sge::renderer::state::core::depth_stencil::stencil::op::keep:
    return D3DSTENCILOP_KEEP;
  case sge::renderer::state::core::depth_stencil::stencil::op::zero:
    return D3DSTENCILOP_ZERO;
  case sge::renderer::state::core::depth_stencil::stencil::op::replace:
    return D3DSTENCILOP_REPLACE;
  case sge::renderer::state::core::depth_stencil::stencil::op::inc_sat:
    return D3DSTENCILOP_INCRSAT;
  case sge::renderer::state::core::depth_stencil::stencil::op::inc_wrap:
    return D3DSTENCILOP_INCR;
  case sge::renderer::state::core::depth_stencil::stencil::op::dec_sat:
    return D3DSTENCILOP_DECRSAT;
  case sge::renderer::state::core::depth_stencil::stencil::op::dec_wrap:
    return D3DSTENCILOP_DECR;
  case sge::renderer::state::core::depth_stencil::stencil::op::invert:
    return D3DSTENCILOP_INVERT;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
