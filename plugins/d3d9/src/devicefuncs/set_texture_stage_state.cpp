//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_texture_stage_state.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/text.hpp>

void sge::d3d9::devicefuncs::set_texture_stage_state(
    IDirect3DDevice9 &_device,
    sge::renderer::texture::stage const _stage,
    D3DTEXTURESTAGESTATETYPE const _type,
    DWORD const _value)
{
  if (_device.SetTextureStageState(_stage.get(), _type, _value) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("SetTextureStageState() failed!"));
}
