//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/state/ffp/transform/matrix_mode.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void sge::opengl::state::ffp::transform::matrix_mode(GLenum const _mode)
{
  sge::opengl::call(::glMatrixMode, _mode);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glMatrixMode failed"), sge::renderer::exception)
}
