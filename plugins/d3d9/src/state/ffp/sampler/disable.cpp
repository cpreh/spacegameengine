//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_texture_stage_state.hpp>
#include <sge/d3d9/state/ffp/sampler/disable.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/stage.hpp>

void sge::d3d9::state::ffp::sampler::disable(
    IDirect3DDevice9 &_device,
    sge::renderer::texture::stage const _stage,
    sge::renderer::caps::texture_stages const _stages)
{
  if (_stage.get() >= _stages.get())
    return;

  sge::d3d9::devicefuncs::set_texture_stage_state(_device, _stage, D3DTSS_COLOROP, D3DTOP_DISABLE);

  sge::d3d9::devicefuncs::set_texture_stage_state(_device, _stage, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
}
