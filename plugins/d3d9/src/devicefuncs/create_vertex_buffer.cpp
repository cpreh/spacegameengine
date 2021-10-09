//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/devicefuncs/create_vertex_buffer.hpp>
#include <sge/d3d9/vertex/d3d_buffer_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>

sge::d3d9::vertex::d3d_buffer_unique_ptr sge::d3d9::devicefuncs::create_vertex_buffer(
    IDirect3DDevice9 &_device,
    sge::renderer::size_type const _size,
    D3DPOOL const _pool,
    sge::d3d9::usage const _usage)
{
  IDirect3DVertexBuffer9 *ret;

  if (_device.CreateVertexBuffer(
          fcppt::cast::size<UINT>(_size

                                  ),
          _usage.get(),
          0, // no FVF
          _pool,
          &ret,
          nullptr) != D3D_OK)
    throw sge::renderer::exception{FCPPT_TEXT("Cannot create vertex buffer!")};

  return sge::d3d9::vertex::d3d_buffer_unique_ptr(ret);
}
