//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/alpha_func.hpp>
#include <sge/d3d9/state/ffp/alpha_test/visitor.hpp>
#include <sge/renderer/state/ffp/alpha_test/enabled.hpp>
#include <sge/renderer/state/ffp/alpha_test/off_fwd.hpp>

sge::d3d9::state::ffp::alpha_test::visitor::result_type
sge::d3d9::state::ffp::alpha_test::visitor::operator()(
    sge::renderer::state::ffp::alpha_test::off const &) const
{
  return sge::d3d9::state::render_vector{sge::d3d9::state::render(D3DRS_ALPHATESTENABLE, FALSE)};
}

sge::d3d9::state::ffp::alpha_test::visitor::result_type
sge::d3d9::state::ffp::alpha_test::visitor::operator()(
    sge::renderer::state::ffp::alpha_test::enabled const &_enabled) const
{
  return sge::d3d9::state::render_vector{
      sge::d3d9::state::render(D3DRS_ALPHATESTENABLE, TRUE),
      sge::d3d9::state::render(
          D3DRS_ALPHAFUNC, sge::d3d9::state::convert::alpha_func(_enabled.func())),
      // TODO: should we change the API for this?
      sge::d3d9::state::render(D3DRS_ALPHAREF, static_cast<DWORD>(_enabled.ref().get() * 256.f))};
}
