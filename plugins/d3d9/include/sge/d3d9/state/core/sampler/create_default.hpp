//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_CORE_SAMPLER_CREATE_DEFAULT_HPP_INCLUDED
#define SGE_D3D9_STATE_CORE_SAMPLER_CREATE_DEFAULT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/core/sampler/object_unique_ptr.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace core
{
namespace sampler
{

sge::d3d9::state::core::sampler::object_unique_ptr create_default(IDirect3DDevice9 &);

}
}
}
}
}

#endif
