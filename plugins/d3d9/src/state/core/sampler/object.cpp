//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_sampler_state.hpp>
#include <sge/d3d9/state/core/sampler/object.hpp>
#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/texture/stage.hpp>

sge::d3d9::state::core::sampler::object::object(
    IDirect3DDevice9 &_device, sge::d3d9::state::core::sampler::state_vector const &_states)
    : sge::renderer::state::core::sampler::object(), device_(_device), states_(_states)
{
}

sge::d3d9::state::core::sampler::object::~object() {}

void sge::d3d9::state::core::sampler::object::set(sge::renderer::texture::stage const _stage) const
{
  for (sge::d3d9::state::core::sampler::state_vector::const_iterator it(states_.begin());
       it != states_.end();
       ++it)
    sge::d3d9::devicefuncs::set_sampler_state(device_, _stage, it->type(), it->value());
}
