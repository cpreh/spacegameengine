//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/ffp/transform/object.hpp>
#include <sge/d3d9/state/ffp/transform/set_defaults.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <fcppt/enum/make_range.hpp>

void sge::d3d9::state::ffp::transform::set_defaults(
    sge::d3d9::state::ffp::transform::object const &_default)
{
  for (auto const mode : fcppt::enum_::make_range<sge::renderer::state::ffp::transform::mode>())
    _default.set(mode);
}
