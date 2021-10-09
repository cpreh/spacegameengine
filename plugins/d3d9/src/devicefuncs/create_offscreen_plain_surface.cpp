//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/color_format.hpp>
#include <sge/d3d9/devicefuncs/create_offscreen_plain_surface.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::d3d9::surface::d3d_unique_ptr sge::d3d9::devicefuncs::create_offscreen_plain_surface(
    IDirect3DDevice9 &_device,
    sge::renderer::dim2 const &_dim,
    sge::image::color::format const _format,
    D3DPOOL const _pool)
{
  IDirect3DSurface9 *ret;

  if (_device.CreateOffscreenPlainSurface(
          static_cast<UINT>(_dim.w()),
          static_cast<UINT>(_dim.h()),
          sge::d3d9::convert::color_format(_format),
          _pool,
          &ret,
          0) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("CreateOffscreenPlainSurface() failed!"));

  return sge::d3d9::surface::d3d_unique_ptr(ret);
}
