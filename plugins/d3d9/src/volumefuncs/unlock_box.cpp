//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/volumefuncs/unlock_box.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void sge::d3d9::volumefuncs::unlock_box(IDirect3DVolume9 &_volume)
{
  if (_volume.UnlockBox() != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("Vurface::UnlockBox() failed!"));
}
