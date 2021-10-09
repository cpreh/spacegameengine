//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/devicefuncs/create_volume_texture.hpp>
#include <sge/d3d9/texture/mipmap/level_count.hpp>
#include <sge/d3d9/texture/mipmap/usage.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/volume_parameters.hpp>
#include <fcppt/text.hpp>

sge::d3d9::texture::d3d_volume_texture_unique_ptr sge::d3d9::devicefuncs::create_volume_texture(
    IDirect3DDevice9 &_device,
    sge::renderer::texture::volume_parameters const &_params,
    D3DFORMAT const _color_format,
    D3DPOOL const _pool,
    sge::d3d9::usage const _usage)
{
  IDirect3DVolumeTexture9 *ret = 0;

  if (_device.CreateVolumeTexture(
          static_cast<UINT>(_params.size().w()),
          static_cast<UINT>(_params.size().h()),
          static_cast<UINT>(_params.size().d()),
          sge::d3d9::texture::mipmap::level_count(_params.mipmap()),
          _usage.get() | sge::d3d9::texture::mipmap::usage(_params.mipmap()).get(),
          _color_format,
          _pool,
          &ret,
          0) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("CreateTexture() failed!"));

  return sge::d3d9::texture::d3d_volume_texture_unique_ptr(ret);
}
