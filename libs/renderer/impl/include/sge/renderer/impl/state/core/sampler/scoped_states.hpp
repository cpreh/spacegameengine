//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_STATE_CORE_SAMPLER_SCOPED_STATES_HPP_INCLUDED
#define SGE_RENDERER_IMPL_STATE_CORE_SAMPLER_SCOPED_STATES_HPP_INCLUDED

#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>

namespace sge::renderer::impl::state::core::sampler
{

sge::renderer::state::core::sampler::const_optional_object_ref_map
scoped_states(sge::renderer::state::core::sampler::const_object_ref_map const &);

}

#endif
