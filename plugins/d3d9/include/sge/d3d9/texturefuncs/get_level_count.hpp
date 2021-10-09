//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TEXTUREFUNCS_GET_LEVEL_COUNT_HPP_INCLUDED
#define SGE_D3D9_TEXTUREFUNCS_GET_LEVEL_COUNT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>

namespace sge
{
namespace d3d9
{
namespace texturefuncs
{

sge::renderer::texture::mipmap::level_count const get_level_count(IDirect3DBaseTexture9 &);

}
}
}

#endif
