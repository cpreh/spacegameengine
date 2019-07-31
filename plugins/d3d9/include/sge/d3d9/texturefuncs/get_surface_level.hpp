//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTUREFUNCS_GET_SURFACE_LEVEL_HPP_INCLUDED
#define SGE_D3D9_TEXTUREFUNCS_GET_SURFACE_LEVEL_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


namespace sge
{
namespace d3d9
{
namespace texturefuncs
{

sge::d3d9::surface::d3d_unique_ptr
get_surface_level(
	IDirect3DTexture9 &,
	sge::renderer::texture::mipmap::level
);

}
}
}

#endif
