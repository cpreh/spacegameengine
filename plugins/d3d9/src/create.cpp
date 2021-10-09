//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/create.hpp>
#include <sge/d3d9/d3d_unique_ptr.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::d3d_unique_ptr sge::d3d9::create()
{
  IDirect3D9 *const result(::Direct3DCreate9(D3D_SDK_VERSION));

  if (!result)
    throw sge::renderer::exception(FCPPT_TEXT("Initialization of d3d failed!"));

  return sge::d3d9::d3d_unique_ptr(result);
}
