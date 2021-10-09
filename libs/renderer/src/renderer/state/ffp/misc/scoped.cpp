//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/misc/object_fwd.hpp>
#include <sge/renderer/state/ffp/misc/scoped.hpp>
#include <fcppt/reference_impl.hpp>

sge::renderer::state::ffp::misc::scoped::scoped(
    sge::renderer::context::ffp_ref const _context,
    fcppt::reference<sge::renderer::state::ffp::misc::object const> const _state)
    : context_(_context)
{
  context_.get().misc_state(sge::renderer::state::ffp::misc::const_optional_object_ref(_state));
}

sge::renderer::state::ffp::misc::scoped::~scoped()
{
  context_.get().misc_state(sge::renderer::state::ffp::misc::const_optional_object_ref());
}
