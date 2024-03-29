//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/impl/state/core/sampler/null_states.hpp>
#include <sge/renderer/impl/state/core/sampler/scoped_states.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>

sge::renderer::state::core::sampler::scoped::scoped(
    sge::renderer::context::core_ref const _context,
    sge::renderer::state::core::sampler::const_object_ref_map const &_states)
    : context_(_context),
      null_states_(sge::renderer::impl::state::core::sampler::null_states(_states))
{
  context_.get().sampler_state(sge::renderer::impl::state::core::sampler::scoped_states(_states));
}

sge::renderer::state::core::sampler::scoped::~scoped()
{
  context_.get().sampler_state(null_states_);
}
