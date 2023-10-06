//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/clear/stencil_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/clear/stencil_buffer_value.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>

void sge::opengl::clear::stencil_buffer(sge::renderer::clear::stencil_buffer_value const &_value)
{
  sge::opengl::call(::glClearStencil, _value);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glClearStencil failed"), sge::renderer::exception)
}
