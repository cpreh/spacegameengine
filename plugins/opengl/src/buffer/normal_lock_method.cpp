//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/normal_lock_method.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum sge::opengl::buffer::normal_lock_method(sge::renderer::lock_flags::method const _method)
{
  switch (_method)
  {
  case sge::renderer::lock_flags::method::read:
    return GL_READ_ONLY;
  case sge::renderer::lock_flags::method::write:
    return GL_WRITE_ONLY;
  case sge::renderer::lock_flags::method::readwrite:
    return GL_READ_WRITE;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
