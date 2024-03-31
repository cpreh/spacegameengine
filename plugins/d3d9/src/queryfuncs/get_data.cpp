//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/queryfuncs/get_data.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

bool sge::d3d9::queryfuncs::get_data(
    IDirect3DQuery9 &_query, void *const _data, DWORD const _count, DWORD const _flags)
{
  switch (_query.GetData(_data, _count, _flags))
  {
  case S_OK:
    return true;
  case S_FALSE:
  case D3DERR_DEVICELOST:
    return false;
  }

  throw sge::renderer::exception{FCPPT_TEXT("Invalid return value in IDirect3DQuery9::GetData!")};
}
