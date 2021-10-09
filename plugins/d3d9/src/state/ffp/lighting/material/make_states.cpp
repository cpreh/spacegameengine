//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/convert/material.hpp>
#include <sge/d3d9/state/ffp/lighting/material/make_states.hpp>
#include <sge/d3d9/state/ffp/lighting/material/state.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>

sge::d3d9::state::ffp::lighting::material::state const
sge::d3d9::state::ffp::lighting::material::make_states(
    sge::renderer::state::ffp::lighting::material::parameters const &_parameters)
{
  return sge::d3d9::state::ffp::lighting::material::state(
      sge::d3d9::state::convert::material(_parameters));
}
