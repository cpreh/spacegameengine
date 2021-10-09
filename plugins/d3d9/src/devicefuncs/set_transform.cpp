//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_transform.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

namespace
{

void do_set(IDirect3DDevice9 &, D3DTRANSFORMSTATETYPE, D3DMATRIX const &);

}

void sge::d3d9::devicefuncs::set_transform(
    IDirect3DDevice9 &_device, D3DTRANSFORMSTATETYPE const _mode, D3DMATRIX const &_matrix)
{
  if (_mode == D3DTS_TEXTURE0)
  {
    // TODO: make a macro in this for fcppt!
    for (unsigned index = _mode; index <= D3DTS_TEXTURE7; ++index)
      do_set(_device, static_cast<D3DTRANSFORMSTATETYPE>(index), _matrix);

    return;
  }

  do_set(_device, _mode, _matrix);
}

namespace
{

void do_set(IDirect3DDevice9 &_device, D3DTRANSFORMSTATETYPE const _mode, D3DMATRIX const &_matrix)
{
  if (_device.SetTransform(_mode, &_matrix) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("SetTransform() failed!"));
}

}
