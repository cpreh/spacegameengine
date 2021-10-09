//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/pixel_rect.hpp>
#include <sge/d3d9/devicefuncs/set_scissor_rect.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <fcppt/text.hpp>

void sge::d3d9::devicefuncs::set_scissor_rect(
    IDirect3DDevice9 &_device, sge::renderer::target::scissor_area const &_scissor_area)
{
  RECT const d3d_rect(sge::d3d9::convert::pixel_rect(_scissor_area.get()));

  if (_device.SetScissorRect(&d3d_rect) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("SetScissorRect() failed!"));
}
