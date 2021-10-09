//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask_all.hpp>

sge::renderer::state::core::depth_stencil::stencil::write_mask
sge::renderer::state::core::depth_stencil::stencil::write_mask_all()
{
  return sge::renderer::state::core::depth_stencil::stencil::write_mask(~0U);
}
