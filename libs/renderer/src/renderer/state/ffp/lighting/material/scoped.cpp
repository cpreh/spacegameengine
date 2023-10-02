//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/scoped.hpp>
#include <fcppt/reference_impl.hpp>

sge::renderer::state::ffp::lighting::material::scoped::scoped(
    sge::renderer::context::ffp_ref const _context,
    fcppt::reference<sge::renderer::state::ffp::lighting::material::object const> const _state)
    : context_(_context)
{
  context_.get().material_state(
      sge::renderer::state::ffp::lighting::material::const_optional_object_ref(_state));
}

sge::renderer::state::ffp::lighting::material::scoped::~scoped()
{
  context_.get().material_state(
      sge::renderer::state::ffp::lighting::material::const_optional_object_ref());
}
