//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_DEVICEFUNCS_CREATE_TEXTURE_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_CREATE_TEXTURE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/d3d_texture_unique_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

sge::d3d9::texture::d3d_texture_unique_ptr
create_texture(
	IDirect3DDevice9 &,
	sge::renderer::texture::planar_parameters const &,
	D3DFORMAT,
	D3DPOOL,
	sge::d3d9::usage
);

}
}
}

#endif
