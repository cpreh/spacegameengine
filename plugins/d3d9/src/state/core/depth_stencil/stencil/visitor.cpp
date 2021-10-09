//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/core/depth_stencil/stencil/enabled_visitor.hpp>
#include <sge/d3d9/state/core/depth_stencil/stencil/visitor.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off_fwd.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/apply.hpp>

sge::d3d9::state::core::depth_stencil::stencil::visitor::result_type
sge::d3d9::state::core::depth_stencil::stencil::visitor::operator()(
    sge::renderer::state::core::depth_stencil::stencil::off const &) const
{
  return sge::d3d9::state::render_vector{sge::d3d9::state::render(D3DRS_STENCILENABLE, FALSE)};
}

sge::d3d9::state::core::depth_stencil::stencil::visitor::result_type
sge::d3d9::state::core::depth_stencil::stencil::visitor::operator()(
    sge::renderer::state::core::depth_stencil::stencil::enabled const &_enabled) const
{
  return fcppt::container::join(
      sge::d3d9::state::render_vector{
          sge::d3d9::state::render(D3DRS_STENCILENABLE, TRUE),
          sge::d3d9::state::render(D3DRS_STENCILREF, _enabled.ref().get()),
          sge::d3d9::state::render(D3DRS_STENCILMASK, _enabled.read_mask().get()),
          sge::d3d9::state::render(D3DRS_STENCILWRITEMASK, _enabled.write_mask().get())},
      fcppt::variant::apply(
          sge::d3d9::state::core::depth_stencil::stencil::enabled_visitor(),
          _enabled.enabled_variant()));
}
