//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/default.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>

sge::renderer::state::core::rasterizer::parameters
sge::renderer::state::core::rasterizer::default_()
{
  return {
      sge::renderer::state::core::rasterizer::cull_mode::off,
      sge::renderer::state::core::rasterizer::fill_mode::solid,
      sge::renderer::state::core::rasterizer::enable_scissor_test(false)};
}
