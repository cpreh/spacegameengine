//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/fbo/config.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/fbo/const_config_ref.hpp>
#include <sge/opengl/fbo/render_buffer.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>

sge::opengl::fbo::render_buffer::render_buffer(
    sge::opengl::fbo::const_config_ref const _context,
    sge::opengl::internal_color_format const _internal_format,
    sge::renderer::dim2 const &_dim)
    : context_(_context), holder_(_context)
{
  this->bind();

  sge::opengl::call_fun_ref(
      context_.get().renderbuffer_storage(),
      context_.get().renderbuffer_target(),
      fcppt::cast::to_unsigned(_internal_format.get()),
      fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(_dim.w())),
      fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(_dim.h())));

  SGE_OPENGL_CHECK_STATE(
      FCPPT_TEXT("Setting the storage of a render buffer failed."), sge::renderer::exception)
}

sge::opengl::fbo::render_buffer::~render_buffer() = default;

GLuint sge::opengl::fbo::render_buffer::id() const { return holder_.id(); }

void sge::opengl::fbo::render_buffer::bind() const
{
  sge::opengl::call_fun_ref(
      context_.get().bind_renderbuffer(), context_.get().renderbuffer_target(), this->id());

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("Binding a render buffer failed."), sge::renderer::exception)
}
