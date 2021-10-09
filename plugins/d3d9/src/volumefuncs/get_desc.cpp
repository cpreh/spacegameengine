//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/volumefuncs/get_desc.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

D3DVOLUME_DESC const sge::d3d9::volumefuncs::get_desc(IDirect3DVolume9 &_volume)
{
  D3DVOLUME_DESC ret;

  if (_volume.GetDesc(&ret) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("Volume::GetDesc() failed!"));

  return ret;
}
