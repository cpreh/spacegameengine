//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/ffp/transform/set.hpp>
#include <sge/opengl/state/ffp/transform/set_defaults.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <fcppt/enum/make_range.hpp>

void sge::opengl::state::ffp::transform::set_defaults(sge::opengl::context::object &_context)
{
  for (auto mode : fcppt::enum_::make_range<sge::renderer::state::ffp::transform::mode>())
  {
    sge::opengl::state::ffp::transform::set(
        _context, mode, sge::renderer::state::ffp::transform::const_optional_object_ref());
  }
}
