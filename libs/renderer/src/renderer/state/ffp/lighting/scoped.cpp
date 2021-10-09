//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/lighting/object_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/scoped.hpp>
#include <fcppt/reference_impl.hpp>

sge::renderer::state::ffp::lighting::scoped::scoped(
    sge::renderer::context::ffp_ref const _context,
    fcppt::reference<sge::renderer::state::ffp::lighting::object const> const _state)
    : context_(_context)
{
  context_.get().lighting_state(
      sge::renderer::state::ffp::lighting::const_optional_object_ref(_state));
}

sge::renderer::state::ffp::lighting::scoped::~scoped()
{
  context_.get().lighting_state(sge::renderer::state::ffp::lighting::const_optional_object_ref());
}
