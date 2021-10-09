//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/set_defaults.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/core/set_defaults.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/set_defaults.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>

void sge::d3d9::state::set_defaults(
    IDirect3DDevice9 &_device,
    sge::d3d9::state::core::defaults const &_core_defaults,
    sge::d3d9::state::ffp::defaults const &_ffp_defaults,
    sge::renderer::caps::light_indices const _light_indices,
    sge::renderer::caps::texture_stages const _texture_stages)
{
  sge::d3d9::state::core::set_defaults(_core_defaults, _texture_stages);

  sge::d3d9::state::ffp::set_defaults(_device, _ffp_defaults, _light_indices, _texture_stages);
}
