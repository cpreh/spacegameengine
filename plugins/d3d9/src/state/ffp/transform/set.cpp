//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/ffp/transform/object.hpp>
#include <sge/d3d9/state/ffp/transform/set.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/maybe.hpp>

void sge::d3d9::state::ffp::transform::set(
    sge::renderer::state::ffp::transform::mode const _mode,
    sge::renderer::state::ffp::transform::const_optional_object_ref const &_opt_state,
    sge::d3d9::state::ffp::transform::object const &_default)
{
  fcppt::optional::maybe(
      _opt_state,
      [&_default]() { return fcppt::make_cref(_default); },
      [](fcppt::reference<sge::renderer::state::ffp::transform::object const> const _state)
      {
        return fcppt::make_cref(
            fcppt::cast::static_downcast<sge::d3d9::state::ffp::transform::object const &>(
                _state.get()));
      })
      .get()
      .set(_mode);
}
