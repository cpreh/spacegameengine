//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/profile/shader_type.hpp>
#include <sge/opengl/cg/profile/convert_shader_type.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>

CGGLenum
sge::opengl::cg::profile::convert_shader_type(sge::cg::profile::shader_type const _shader_type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_shader_type)
  {
  case sge::cg::profile::shader_type::vertex:
    return CG_GL_VERTEX;
  case sge::cg::profile::shader_type::pixel:
    return CG_GL_FRAGMENT;
  case sge::cg::profile::shader_type::geometry:
    return CG_GL_GEOMETRY;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_shader_type);
}
