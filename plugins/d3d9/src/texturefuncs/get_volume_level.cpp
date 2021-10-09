//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texturefuncs/get_volume_level.hpp>
#include <sge/d3d9/volume/d3d_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>

sge::d3d9::volume::d3d_unique_ptr sge::d3d9::texturefuncs::get_volume_level(
    IDirect3DVolumeTexture9 &_texture, sge::renderer::texture::mipmap::level const _level)
{
  IDirect3DVolume9 *result;

  if (_texture.GetVolumeLevel(_level.get(), &result) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("GetVolumeLevel failed!"));

  return sge::d3d9::volume::d3d_unique_ptr(result);
}
