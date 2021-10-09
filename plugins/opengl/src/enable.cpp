//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

void sge::opengl::enable(GLenum const _what)
{
  sge::opengl::call(::glEnable, _what);

  SGE_OPENGL_CHECK_STATE(
      (fcppt::format(FCPPT_TEXT("glEnable %1% failed")) % _what).str(), sge::renderer::exception)
}
