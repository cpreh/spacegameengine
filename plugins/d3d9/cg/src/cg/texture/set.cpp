//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/check_state.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/d3d9/cg/texture/set.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgD3D9.h>
#include <fcppt/config/external_end.hpp>

void sge::d3d9::cg::texture::set(
    IDirect3DDevice9 &_device,
    sge::cg::parameter::object const &_parameter,
    IDirect3DBaseTexture9 *const _texture)
{
  sge::d3d9::cg::scoped_device const context(_device);

  if (::cgD3D9SetTexture(_parameter.get(), _texture) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("cgD3D9SetTexture failed"));

  SGE_CG_CHECK_STATE(FCPPT_TEXT("cgD3D9SetTexture failed"), sge::renderer::exception)
}
