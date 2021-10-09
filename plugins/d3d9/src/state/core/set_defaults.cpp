//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/core/defaults.hpp>
#include <sge/d3d9/state/core/set_defaults.hpp>
#include <sge/d3d9/state/core/blend/object.hpp>
#include <sge/d3d9/state/core/depth_stencil/object.hpp>
#include <sge/d3d9/state/core/rasterizer/object.hpp>
#include <sge/d3d9/state/core/sampler/set_defaults.hpp>
#include <sge/renderer/caps/texture_stages.hpp>

void sge::d3d9::state::core::set_defaults(
    sge::d3d9::state::core::defaults const &_defaults,
    sge::renderer::caps::texture_stages const _stages)
{
  _defaults.blend().set();

  _defaults.depth_stencil().set();

  _defaults.rasterizer().set();

  sge::d3d9::state::core::sampler::set_defaults(_defaults.sampler(), _stages);
}
