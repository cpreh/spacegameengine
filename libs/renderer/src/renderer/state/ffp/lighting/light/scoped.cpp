//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/light/scoped.hpp>

sge::renderer::state::ffp::lighting::light::scoped::scoped(
    sge::renderer::context::ffp_ref const _context,
    sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &_states)
    : context_(_context)
{
  context_.get().lights_state(_states);
}

sge::renderer::state::ffp::lighting::light::scoped::~scoped()
{
  context_.get().lights_state(
      sge::renderer::state::ffp::lighting::light::const_object_ref_vector());
}
