//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_CORE_DEPTH_STENCIL_CREATE_HPP_INCLUDED
#define SGE_D3D9_STATE_CORE_DEPTH_STENCIL_CREATE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace core
{
namespace depth_stencil
{

sge::renderer::state::core::depth_stencil::object_unique_ptr
create(
	IDirect3DDevice9 &,
	sge::renderer::state::core::depth_stencil::parameters const &
);

}
}
}
}
}

#endif
