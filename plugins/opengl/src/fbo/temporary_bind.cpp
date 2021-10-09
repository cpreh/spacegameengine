//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/fbo/bind.hpp>
#include <sge/opengl/fbo/const_config_ref.hpp>
#include <sge/opengl/fbo/last_context.hpp>
#include <sge/opengl/fbo/last_context_ref.hpp>
#include <sge/opengl/fbo/object.hpp>
#include <sge/opengl/fbo/temporary_bind.hpp>

sge::opengl::fbo::temporary_bind::temporary_bind(
    sge::opengl::fbo::const_config_ref const _context,
    sge::opengl::fbo::last_context_ref const _last_context,
    sge::opengl::fbo::object const &_object)
    : context_(_context),
      last_context_(_last_context),
      last_buffer_(last_context_.get().last_buffer())
{
  _object.bind();
}

sge::opengl::fbo::temporary_bind::~temporary_bind()
{
  sge::opengl::fbo::bind(context_.get(), last_buffer_);

  last_context_.get().last_buffer(last_buffer_);
}
