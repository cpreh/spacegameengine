//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/sampler/disable.hpp>
#include <sge/d3d9/state/ffp/sampler/object.hpp>
#include <sge/d3d9/state/ffp/sampler/set_defaults.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/stage.hpp>

void sge::d3d9::state::ffp::sampler::set_defaults(
    IDirect3DDevice9 &_device,
    sge::d3d9::state::ffp::sampler::object const &_default,
    sge::renderer::caps::texture_stages const _stages)
{
  _default.set(sge::renderer::texture::stage(0u));

  sge::d3d9::state::ffp::sampler::disable(_device, sge::renderer::texture::stage(1u), _stages);
}
