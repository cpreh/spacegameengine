//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>
#include <sge/d3d9/systemfuncs/get_caps.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

D3DCAPS9
sge::d3d9::systemfuncs::get_caps(IDirect3D9 &_system, sge::d3d9::device_index const _index)
{
  D3DCAPS9 caps;

  if (_system.GetDeviceCaps(_index.get(), D3DDEVTYPE_HAL, &caps) != D3D_OK)
    throw sge::renderer::exception{FCPPT_TEXT("GetDeviceCaps failed")};

  return caps;
}
