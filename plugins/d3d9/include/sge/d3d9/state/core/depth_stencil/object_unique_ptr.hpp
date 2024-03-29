//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_CORE_DEPTH_STENCIL_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SGE_D3D9_STATE_CORE_DEPTH_STENCIL_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sge/d3d9/state/core/depth_stencil/object_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

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

typedef fcppt::unique_ptr<sge::d3d9::state::core::depth_stencil::object> object_unique_ptr;

}
}
}
}
}

#endif
