//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/buffer/range_lock_method.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::buffer::range_lock_method(sge::renderer::lock_flags::method const _method)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_method)
  {
  case sge::renderer::lock_flags::method::read:
    return GL_MAP_READ_BIT;
  case sge::renderer::lock_flags::method::write:
    return GL_MAP_WRITE_BIT // NOLINT(hicpp-signed-bitwise)
           | GL_MAP_INVALIDATE_RANGE_BIT;
  case sge::renderer::lock_flags::method::readwrite:
    return GL_MAP_READ_BIT // NOLINT(hicpp-signed-bitwise)
           | GL_MAP_WRITE_BIT;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_method);
}
