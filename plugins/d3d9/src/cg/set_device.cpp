//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/check_state.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/set_device.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgD3D9.h>
#include <fcppt/config/external_end.hpp>

void sge::d3d9::cg::set_device(IDirect3DDevice9 *const _device)
{
  if (::cgD3D9SetDevice(_device) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("cgD3D9SetDevice failed"));

  SGE_CG_CHECK_STATE(FCPPT_TEXT("cgD3D9SetDevice failed"), sge::renderer::exception)
}
