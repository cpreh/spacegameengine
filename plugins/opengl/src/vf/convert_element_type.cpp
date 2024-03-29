//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::vf::convert_element_type(sge::renderer::vf::dynamic::element_type const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sge::renderer::vf::dynamic::element_type::float_:
    return GL_FLOAT;
  case sge::renderer::vf::dynamic::element_type::double_:
    return GL_DOUBLE;
  case sge::renderer::vf::dynamic::element_type::byte:
    return GL_BYTE;
  case sge::renderer::vf::dynamic::element_type::ubyte:
    return GL_UNSIGNED_BYTE;
  case sge::renderer::vf::dynamic::element_type::short_:
    return GL_SHORT;
  case sge::renderer::vf::dynamic::element_type::ushort:
    return GL_UNSIGNED_SHORT;
  case sge::renderer::vf::dynamic::element_type::int_:
    return GL_INT;
  case sge::renderer::vf::dynamic::element_type::uint:
    return GL_UNSIGNED_INT;
  }

  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
