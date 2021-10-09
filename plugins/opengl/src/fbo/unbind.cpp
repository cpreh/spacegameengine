//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/fbo/bind.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/no_buffer.hpp>
#include <sge/opengl/fbo/unbind.hpp>

void sge::opengl::fbo::unbind(sge::opengl::fbo::config const &_context)
{
  sge::opengl::fbo::bind(_context, sge::opengl::fbo::no_buffer());
}
