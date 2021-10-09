//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_CORE_SAMPLER_SET_DEFAULTS_HPP_INCLUDED
#define SGE_D3D9_STATE_CORE_SAMPLER_SET_DEFAULTS_HPP_INCLUDED

#include <sge/d3d9/state/core/sampler/object_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>

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

void set_defaults(
    sge::d3d9::state::core::sampler::object const &, sge::renderer::caps::texture_stages);

}
}
}
}
}

#endif
