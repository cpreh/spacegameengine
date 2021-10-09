//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/get_swap_chain.hpp>
#include <sge/d3d9/swapchain/d3d_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::swapchain::d3d_unique_ptr
sge::d3d9::devicefuncs::get_swap_chain(IDirect3DDevice9 &_device, UINT const _index)
{
  IDirect3DSwapChain9 *result;

  if (_device.GetSwapChain(_index, &result) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("GetSwapChain failed!"));

  return sge::d3d9::swapchain::d3d_unique_ptr(result);
}
