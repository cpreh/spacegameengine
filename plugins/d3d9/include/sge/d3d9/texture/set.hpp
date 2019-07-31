//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_SET_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_SET_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

void
set(
	IDirect3DDevice9 &,
	renderer::texture::stage,
	renderer::texture::const_optional_base_ref const &
);

}
}
}

#endif
