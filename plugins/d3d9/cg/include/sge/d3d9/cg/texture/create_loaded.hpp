//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_CG_TEXTURE_CREATE_LOADED_HPP_INCLUDED
#define SGE_D3D9_CG_TEXTURE_CREATE_LOADED_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace cg
{
namespace texture
{

sge::renderer::cg::loaded_texture_unique_ptr create_loaded(
    IDirect3DDevice9 &,
    sge::cg::parameter::object const &,
    sge::renderer::texture::base &,
    sge::renderer::caps::texture_stages);

}
}
}
}

#endif
