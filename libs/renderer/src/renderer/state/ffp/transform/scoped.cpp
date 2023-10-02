//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object_fwd.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <fcppt/reference_impl.hpp>

sge::renderer::state::ffp::transform::scoped::scoped(
    sge::renderer::context::ffp_ref const _context,
    sge::renderer::state::ffp::transform::mode const _mode,
    fcppt::reference<sge::renderer::state::ffp::transform::object const> const _object)
    : context_(_context), mode_(_mode)
{
  context_.get().transform(
      mode_, sge::renderer::state::ffp::transform::const_optional_object_ref(_object));
}

sge::renderer::state::ffp::transform::scoped::~scoped()
{
  context_.get().transform(
      mode_, sge::renderer::state::ffp::transform::const_optional_object_ref());
}
