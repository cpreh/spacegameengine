//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/devicefuncs/create_texture.hpp>
#include <sge/d3d9/texture/d3d_texture_unique_ptr.hpp>
#include <sge/d3d9/texture/mipmap/level_count.hpp>
#include <sge/d3d9/texture/mipmap/usage.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/output.hpp>

sge::d3d9::texture::d3d_texture_unique_ptr sge::d3d9::devicefuncs::create_texture(
    IDirect3DDevice9 &_device,
    sge::renderer::texture::planar_parameters const &_params,
    D3DFORMAT const _color_format,
    D3DPOOL const _pool,
    sge::d3d9::usage const _usage)
{
  IDirect3DTexture9 *ret(nullptr);

  if (_device.CreateTexture(
          static_cast<UINT>(_params.size().w()),
          static_cast<UINT>(_params.size().h()),
          sge::d3d9::texture::mipmap::level_count(_params.mipmap()),
          _usage.get() | sge::d3d9::texture::mipmap::usage(_params.mipmap()).get(),
          _color_format,
          _pool,
          &ret,
          0) != D3D_OK)
    throw sge::renderer::exception(
        FCPPT_TEXT("CreateTexture() with size ") + fcppt::output_to_fcppt_string(_params.size()) +
        FCPPT_TEXT(" and color format ") +
        sge::image::color::format_to_string(_params.format().format()) + FCPPT_TEXT(" failed!"));

  return sge::d3d9::texture::d3d_texture_unique_ptr(ret);
}
