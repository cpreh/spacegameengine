//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texturefuncs/get_level_count.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>

sge::renderer::texture::mipmap::level_count const
sge::d3d9::texturefuncs::get_level_count(IDirect3DBaseTexture9 &_texture)
{
  return sge::renderer::texture::mipmap::level_count(_texture.GetLevelCount());
}
