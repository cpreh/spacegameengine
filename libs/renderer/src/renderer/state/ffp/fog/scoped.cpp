//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/fog/object_fwd.hpp>
#include <sge/renderer/state/ffp/fog/scoped.hpp>

sge::renderer::state::ffp::fog::scoped::scoped(
    sge::renderer::context::ffp_ref const _context,
    fcppt::reference<sge::renderer::state::ffp::fog::object const> const _state)
    : context_(_context)
{
  context_.get().fog_state(sge::renderer::state::ffp::fog::const_optional_object_ref(_state));
}

sge::renderer::state::ffp::fog::scoped::~scoped()
{
  context_.get().fog_state(sge::renderer::state::ffp::fog::const_optional_object_ref());
}
