//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/stencil_func.hpp>
#include <sge/d3d9/state/convert/stencil_op.hpp>
#include <sge/d3d9/state/core/depth_stencil/stencil/one_side.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/desc.hpp>

sge::d3d9::state::render_vector sge::d3d9::state::core::depth_stencil::stencil::one_side(
    sge::renderer::state::core::depth_stencil::stencil::desc const &_desc)
{
  return sge::d3d9::state::render_vector{
      sge::d3d9::state::render(
          D3DRS_STENCILFAIL, sge::d3d9::state::convert::stencil_op(_desc.fail_op().get())),
      sge::d3d9::state::render(
          D3DRS_STENCILZFAIL, sge::d3d9::state::convert::stencil_op(_desc.depth_fail_op().get())),
      sge::d3d9::state::render(
          D3DRS_STENCILPASS, sge::d3d9::state::convert::stencil_op(_desc.pass_op().get())),
      sge::d3d9::state::render(
          D3DRS_STENCILFUNC, sge::d3d9::state::convert::stencil_func(_desc.func()))};
}
