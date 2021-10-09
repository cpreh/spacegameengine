//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/attach_render_buffer.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void sge::opengl::fbo::attach_render_buffer(
    sge::opengl::fbo::config const &_context,
    sge::opengl::fbo::attachment_type const _what,
    GLuint const _buffer)
{
  sge::opengl::call_fun_ref(
      _context.framebuffer_renderbuffer(),
      _context.framebuffer_target(),
      _what.get(),
      _context.renderbuffer_target(),
      _buffer);

  SGE_OPENGL_CHECK_STATE(
      FCPPT_TEXT("Attaching a render buffer to a frame buffer failed!"), sge::renderer::exception)
}
