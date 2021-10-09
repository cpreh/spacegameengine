//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_CG_TEXTURE_ACTIVATE_HPP_INCLUDED
#define SGE_D3D9_CG_TEXTURE_ACTIVATE_HPP_INCLUDED

#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>

namespace sge
{
namespace d3d9
{
namespace cg
{
namespace texture
{

sge::renderer::texture::stage const activate(sge::renderer::cg::loaded_texture const &);

}
}
}
}

#endif
