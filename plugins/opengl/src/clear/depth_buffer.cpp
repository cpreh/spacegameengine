//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/clear/depth_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>

void sge::opengl::clear::depth_buffer(sge::renderer::clear::depth_buffer_value const &_value)
{
  sge::opengl::call(::glClearDepth, fcppt::cast::size<GLdouble>(_value));

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glClearDepth failed"), sge::renderer::exception)
}
