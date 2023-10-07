//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/ffp/transform/context.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>

void sge::opengl::state::ffp::transform::set_matrix(
    sge::opengl::context::object &_context, sge::renderer::matrix4 const &_matrix)
{
  fcppt::optional::maybe(
      sge::opengl::context::use<sge::opengl::state::ffp::transform::context>(
          fcppt::make_ref(_context), _context.info())
          .load_transpose_matrix_f(),
      [&_matrix]
      {
        sge::opengl::call(::glLoadMatrixf, _matrix.storage().data());

        SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glLoadMatrixf failed"), sge::renderer::exception)
      },
      [&_matrix](sge::opengl::state::ffp::transform::context::load_transpose_matrix_f_ref const
                     _load_matrix)
      {
        _load_matrix.get()(_matrix.storage().data());

        SGE_OPENGL_CHECK_STATE(
            FCPPT_TEXT("glLoadTransposeMatrixf failed"), sge::renderer::exception)
      });
}
