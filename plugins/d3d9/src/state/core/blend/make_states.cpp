//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/core/blend/alpha_visitor.hpp>
#include <sge/d3d9/state/core/blend/make_states.hpp>
#include <sge/d3d9/state/core/blend/write_mask.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/apply.hpp>

sge::d3d9::state::render_vector sge::d3d9::state::core::blend::make_states(
    sge::renderer::state::core::blend::parameters const &_parameters)
{
  return fcppt::container::join(
      sge::d3d9::state::render_vector{
          sge::d3d9::state::core::blend::write_mask(_parameters.write_mask())},
      fcppt::variant::apply(
          sge::d3d9::state::core::blend::alpha_visitor(), _parameters.alpha_variant()));
}
