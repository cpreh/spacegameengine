//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/convert/primitive_type.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::convert::primitive_type(sge::renderer::primitive_type const _primitive_type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_primitive_type)
  {
  case sge::renderer::primitive_type::point_list:
    return GL_POINTS;
  case renderer::primitive_type::line_list:
    return GL_LINES;
  case renderer::primitive_type::line_strip:
    return GL_LINE_STRIP;
  case renderer::primitive_type::triangle_list:
    return GL_TRIANGLES;
  case renderer::primitive_type::triangle_strip:
    return GL_TRIANGLE_STRIP;
  case renderer::primitive_type::triangle_fan:
    return GL_TRIANGLE_FAN;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_primitive_type);
}
