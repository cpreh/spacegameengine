//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/core/depth_stencil/make_states.hpp>
#include <sge/d3d9/state/core/depth_stencil/depth/visitor.hpp>
#include <sge/d3d9/state/core/depth_stencil/stencil/visitor.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/apply.hpp>

sge::d3d9::state::render_vector sge::d3d9::state::core::depth_stencil::make_states(
    sge::renderer::state::core::depth_stencil::parameters const &_parameters)
{
  return fcppt::container::join(
      fcppt::variant::apply(
          sge::d3d9::state::core::depth_stencil::depth::visitor(), _parameters.depth_variant()),
      fcppt::variant::apply(
          sge::d3d9::state::core::depth_stencil::stencil::visitor(),
          _parameters.stencil_variant()));
}
