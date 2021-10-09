//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/create_query.hpp>
#include <sge/d3d9/query/d3d_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::query::d3d_unique_ptr
sge::d3d9::devicefuncs::create_query(IDirect3DDevice9 &_device, D3DQUERYTYPE const _type)
{
  IDirect3DQuery9 *result;

  if (_device.CreateQuery(_type, &result) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("CreateQuery failed!"));

  return sge::d3d9::query::d3d_unique_ptr(result);
}
