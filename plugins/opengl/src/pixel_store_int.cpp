//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/pixel_store_int.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>

void sge::opengl::pixel_store_int(GLenum const _what, GLint const _value)
{
  sge::opengl::call(::glPixelStorei, _what, _value);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glPixelStorei failed!"), sge::renderer::exception)
}
