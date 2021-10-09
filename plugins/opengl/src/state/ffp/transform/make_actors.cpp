//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/ffp/transform/actor.hpp>
#include <sge/opengl/state/ffp/transform/actor_vector.hpp>
#include <sge/opengl/state/ffp/transform/context.hpp>
#include <sge/opengl/state/ffp/transform/make_actors.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix_and_mode.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <fcppt/math/matrix/transpose.hpp>

sge::opengl::state::ffp::transform::actor_vector sge::opengl::state::ffp::transform::make_actors(
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::ffp::transform::parameters const &_parameters)
{
  return sge::opengl::state::ffp::transform::actor_vector{sge::opengl::state::ffp::transform::actor{
      [_context,
       matrix = _parameters.matrix()](sge::renderer::state::ffp::transform::mode const _mode)
      {
        sge::opengl::state::ffp::transform::set_matrix_and_mode(
            _context.get(),
            _mode,
            sge::opengl::context::use<sge::opengl::state::ffp::transform::context>(
                _context, _context.get().info())
                    .have_transpose()
                ? matrix
                : fcppt::math::matrix::transpose(matrix));
      }}};
}
