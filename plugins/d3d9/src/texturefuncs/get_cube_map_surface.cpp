//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/cube_side.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/texturefuncs/get_cube_map_surface.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>

sge::d3d9::surface::d3d_unique_ptr sge::d3d9::texturefuncs::get_cube_map_surface(
    IDirect3DCubeTexture9 &_texture,
    sge::renderer::texture::cube_side const _side,
    sge::renderer::texture::mipmap::level const _level)
{
  IDirect3DSurface9 *result;

  if (_texture.GetCubeMapSurface(sge::d3d9::convert::cube_side(_side), _level.get(), &result) !=
      D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("GetCubeMapSurface failed!"));

  return sge::d3d9::surface::d3d_unique_ptr(result);
}
