//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/convert/index_format.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::convert::index_format(sge::renderer::index::dynamic::format const _format)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
  case sge::renderer::index::dynamic::format::i16:
    return GL_UNSIGNED_SHORT;
  case sge::renderer::index::dynamic::format::i32:
    return GL_UNSIGNED_INT;
  }

  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
