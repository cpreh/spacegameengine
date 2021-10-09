//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/depth_stencil/stencil/back.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/front.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/separate.hpp>

sge::renderer::state::core::depth_stencil::stencil::separate::separate(
    sge::renderer::state::core::depth_stencil::stencil::front const &_front,
    sge::renderer::state::core::depth_stencil::stencil::back const &_back)
    : front_(_front), back_(_back)
{
}

sge::renderer::state::core::depth_stencil::stencil::front const &
sge::renderer::state::core::depth_stencil::stencil::separate::front() const
{
  return front_;
}

sge::renderer::state::core::depth_stencil::stencil::back const &
sge::renderer::state::core::depth_stencil::stencil::separate::back() const
{
  return back_;
}
