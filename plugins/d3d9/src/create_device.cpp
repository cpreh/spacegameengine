//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/create_device.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>
#include <sge/d3d9/parameters/tnl_caps.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::d3d_device_unique_ptr sge::d3d9::create_device(
    IDirect3D9 &_system, sge::d3d9::device_index const _index, D3DPRESENT_PARAMETERS &_parameters)
{
  IDirect3DDevice9 *ret;

  if (_system.CreateDevice(
          _index.get(),
          D3DDEVTYPE_HAL,
          _parameters.hDeviceWindow,
          sge::d3d9::parameters::tnl_caps(_system, _index),
          &_parameters,
          &ret) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("Failed to initialize the d3d9 renderer!"));

  return sge::d3d9::d3d_device_unique_ptr(ret);
}
