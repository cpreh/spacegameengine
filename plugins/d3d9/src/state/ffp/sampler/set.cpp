//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/sampler/disable.hpp>
#include <sge/d3d9/state/ffp/sampler/object.hpp>
#include <sge/d3d9/state/ffp/sampler/set.hpp>
#include <sge/d3d9/state/ffp/sampler/set_defaults.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/strong_typedef_arithmetic.hpp>

void sge::d3d9::state::ffp::sampler::set(
    IDirect3DDevice9 &_device,
    sge::renderer::state::ffp::sampler::const_object_ref_vector const &_states,
    sge::d3d9::state::ffp::sampler::object const &_default,
    sge::renderer::caps::texture_stages const _stages)
{
  if (_states.empty())
  {
    sge::d3d9::state::ffp::sampler::set_defaults(_device, _default, _stages);

    return;
  }

  sge::renderer::texture::stage stage(0u);

  for (auto const &state : _states)
    static_cast<sge::d3d9::state::ffp::sampler::object const &>(state.get()).set(stage++);

  sge::d3d9::state::ffp::sampler::disable(_device, stage, _stages);
}
