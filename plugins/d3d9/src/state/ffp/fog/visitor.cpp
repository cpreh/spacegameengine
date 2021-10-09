//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_color.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/float_to_dword.hpp>
#include <sge/d3d9/state/convert/fog_mode.hpp>
#include <sge/d3d9/state/ffp/fog/visitor.hpp>
#include <sge/renderer/state/ffp/fog/enabled.hpp>
#include <sge/renderer/state/ffp/fog/off_fwd.hpp>

sge::d3d9::state::ffp::fog::visitor::result_type
sge::d3d9::state::ffp::fog::visitor::operator()(sge::renderer::state::ffp::fog::off const &) const
{
  return sge::d3d9::state::render_vector{sge::d3d9::state::render(D3DRS_FOGENABLE, FALSE)};
}

sge::d3d9::state::ffp::fog::visitor::result_type sge::d3d9::state::ffp::fog::visitor::operator()(
    sge::renderer::state::ffp::fog::enabled const &_enabled) const
{
  return sge::d3d9::state::render_vector{
      sge::d3d9::state::render(D3DRS_FOGENABLE, TRUE),
      sge::d3d9::state::render(
          D3DRS_FOGTABLEMODE, sge::d3d9::state::convert::fog_mode(_enabled.mode())),
      sge::d3d9::state::render(
          D3DRS_FOGCOLOR, sge::d3d9::convert::to_color(_enabled.color().get())),
      sge::d3d9::state::render(
          D3DRS_FOGSTART, sge::d3d9::state::convert::float_to_dword(_enabled.start().get())),
      sge::d3d9::state::render(
          D3DRS_FOGEND, sge::d3d9::state::convert::float_to_dword(_enabled.end().get())),
      sge::d3d9::state::render(
          D3DRS_FOGDENSITY, sge::d3d9::state::convert::float_to_dword(_enabled.density().get()))};
}
