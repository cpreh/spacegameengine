//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/check_state_always.hpp>
#include <sge/opengl/check_state_once.hpp>
#if !defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/error_string.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#endif

void sge::opengl::check_state_once()
{
#if !defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
  GLenum ret(GL_NO_ERROR);

  fcppt::string errors;

  while ((ret = sge::opengl::call(::glGetError)) != GL_NO_ERROR)
    errors += sge::opengl::error_string(ret) + FCPPT_TEXT(", ");

  if (ret != GL_NO_ERROR)
  {
    // erase last ", "
    errors.erase(errors.end() - 2, errors.end());

    throw sge::renderer::exception(FCPPT_TEXT("Cumulative GL errors: ") + errors);
  }
#endif
}
