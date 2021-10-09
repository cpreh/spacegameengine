//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_CG_TEXTURE_ASSIGNED_STAGE_HPP_INCLUDED
#define SGE_D3D9_CG_TEXTURE_ASSIGNED_STAGE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texture/base_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/stage.hpp>

namespace sge
{
namespace d3d9
{
namespace cg
{
namespace texture
{

sge::renderer::texture::stage const assigned_stage(
    IDirect3DDevice9 &, sge::d3d9::texture::base const &, sge::renderer::caps::texture_stages);

}
}
}
}

#endif
