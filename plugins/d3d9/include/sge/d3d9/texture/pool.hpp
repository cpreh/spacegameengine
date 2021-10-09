//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TEXTURE_POOL_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_POOL_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace texture
{

D3DPOOL
pool(renderer::resource_flags_field const &, renderer::texture::capabilities_field const &);

}
}
}

#endif
