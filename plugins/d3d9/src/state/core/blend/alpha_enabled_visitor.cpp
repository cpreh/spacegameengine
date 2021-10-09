//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/dest_blend_func.hpp>
#include <sge/d3d9/state/convert/source_blend_func.hpp>
#include <sge/d3d9/state/core/blend/alpha_enabled_visitor.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>

sge::d3d9::state::core::blend::alpha_enabled_visitor::result_type
sge::d3d9::state::core::blend::alpha_enabled_visitor::operator()(
    sge::renderer::state::core::blend::combined const &_combined) const
{
  return sge::d3d9::state::render_vector{
      sge::d3d9::state::render(D3DRS_SEPARATEALPHABLENDENABLE, FALSE),
      sge::d3d9::state::render(
          D3DRS_SRCBLEND, sge::d3d9::state::convert::source_blend_func(_combined.source())),
      sge::d3d9::state::render(
          D3DRS_DESTBLEND, sge::d3d9::state::convert::dest_blend_func(_combined.dest()))};
}

sge::d3d9::state::core::blend::alpha_enabled_visitor::result_type
sge::d3d9::state::core::blend::alpha_enabled_visitor::operator()(
    sge::renderer::state::core::blend::separate const &_separate) const
{
  return sge::d3d9::state::render_vector{
      sge::d3d9::state::render(D3DRS_SEPARATEALPHABLENDENABLE, TRUE),
      sge::d3d9::state::render(
          D3DRS_SRCBLEND,
          sge::d3d9::state::convert::source_blend_func(_separate.color_source().get())),
      sge::d3d9::state::render(
          D3DRS_DESTBLEND,
          sge::d3d9::state::convert::dest_blend_func(_separate.color_dest().get())),
      sge::d3d9::state::render(
          D3DRS_SRCBLENDALPHA,
          sge::d3d9::state::convert::source_blend_func(_separate.alpha_source().get())),
      sge::d3d9::state::render(
          D3DRS_DESTBLENDALPHA,
          sge::d3d9::state::convert::dest_blend_func(_separate.alpha_dest().get()))};
}
