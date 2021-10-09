//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/optional_object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/matrix.hpp>
#include <sge/sprite/optional_projection_dim.hpp>
#include <sge/sprite/projection_dim.hpp>
#include <sge/sprite/projection_matrix.hpp>
#include <sge/sprite/projection_matrix_fixed.hpp>
#include <sge/sprite/state/with_transform.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>

sge::renderer::state::ffp::transform::optional_object_unique_ptr
sge::sprite::state::with_transform::make(
    sge::renderer::device::ffp_ref const _device,
    sge::renderer::context::ffp &_context,
    sge::sprite::state::with_transform::optional_extra_option const &_projection_dim)
{
  return fcppt::optional::map(
      fcppt::optional::maybe(
          _projection_dim,
          [&_context] { return sge::sprite::projection_matrix(_context.target().viewport()); },
          [](sge::sprite::projection_dim const &_dim)
          { return sge::sprite::projection_matrix_fixed(_dim); }),
      [&_device](sge::sprite::matrix const &_matrix)
      {
        return _device.get().create_transform_state(
            sge::renderer::state::ffp::transform::parameters(_matrix));
      });
}

void sge::sprite::state::with_transform::set(
    sge::renderer::context::ffp &_context,
    fcppt::reference<sge::renderer::state::ffp::transform::object const> const _state)
{
  _context.transform(
      sge::renderer::state::ffp::transform::mode::projection,
      sge::renderer::state::ffp::transform::const_optional_object_ref(_state));
}

void sge::sprite::state::with_transform::unset(sge::renderer::context::ffp &_context)
{
  _context.transform(
      sge::renderer::state::ffp::transform::mode::projection,
      sge::renderer::state::ffp::transform::const_optional_object_ref());
}
