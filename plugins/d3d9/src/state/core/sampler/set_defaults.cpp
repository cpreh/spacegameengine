//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/core/sampler/object.hpp>
#include <sge/d3d9/state/core/sampler/set_defaults.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/stage.hpp>

void sge::d3d9::state::core::sampler::set_defaults(
    sge::d3d9::state::core::sampler::object const &_default,
    sge::renderer::caps::texture_stages const _stages)
{
  for (sge::renderer::texture::stage stage(0u); stage.get() < _stages.get(); ++stage)
    _default.set(stage);
}
