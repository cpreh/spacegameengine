//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/cube_side.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <fcppt/assert/unreachable.hpp>

D3DCUBEMAP_FACES
sge::d3d9::convert::cube_side(sge::renderer::texture::cube_side const _side)
{
  switch (_side)
  {
  case sge::renderer::texture::cube_side::front:
    return D3DCUBEMAP_FACE_NEGATIVE_Z;
  case sge::renderer::texture::cube_side::back:
    return D3DCUBEMAP_FACE_POSITIVE_Z;
  case sge::renderer::texture::cube_side::left:
    return D3DCUBEMAP_FACE_NEGATIVE_X;
  case sge::renderer::texture::cube_side::right:
    return D3DCUBEMAP_FACE_POSITIVE_X;
  case sge::renderer::texture::cube_side::top:
    return D3DCUBEMAP_FACE_POSITIVE_Y;
  case sge::renderer::texture::cube_side::bottom:
    return D3DCUBEMAP_FACE_NEGATIVE_Y;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
