//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/delete_id.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>

void sge::opengl::fbo::delete_id(
    sge::opengl::fbo::config const &_context, sge::opengl::fbo::id const _id)
{
  GLuint const id(_id.get());

  sge::opengl::call_fun_ref(_context.delete_framebuffers(), 1, &id);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glDeleteFramebuffers failed"), sge::renderer::exception)
}
