//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/gen_render_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>

GLuint sge::opengl::fbo::gen_render_buffer(sge::opengl::fbo::config const &_config)
{
  GLuint id{};

  sge::opengl::call_fun_ref(_config.gen_renderbuffers(), 1, &id);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("Generating a render buffer failed."), sge::renderer::exception)

  return id;
}
