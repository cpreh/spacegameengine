//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_CG_PROFILE_CREATE_HPP_INCLUDED
#define SGE_D3D9_CG_PROFILE_CREATE_HPP_INCLUDED

#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/profile/shader_type_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>

namespace sge
{
namespace d3d9
{
namespace cg
{
namespace profile
{

sge::cg::profile::object const create(IDirect3DDevice9 &, sge::cg::profile::shader_type);

}
}
}
}

#endif
