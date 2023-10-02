//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/alpha_test/object_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/scoped.hpp>
#include <fcppt/reference_impl.hpp>

sge::renderer::state::ffp::alpha_test::scoped::scoped(
    sge::renderer::context::ffp_ref const _context,
    fcppt::reference<sge::renderer::state::ffp::alpha_test::object const> const _state)
    : context_(_context)
{
  context_.get().alpha_test_state(
      sge::renderer::state::ffp::alpha_test::const_optional_object_ref(_state));
}

sge::renderer::state::ffp::alpha_test::scoped::~scoped()
{
  context_.get().alpha_test_state(
      sge::renderer::state::ffp::alpha_test::const_optional_object_ref());
}
