//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/profile/shader_type.hpp>
#include <sge/opengl/cg/profile/convert_shader_type.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>

CGGLenum
sge::opengl::cg::profile::convert_shader_type(sge::cg::profile::shader_type const _shader_type)
{
  switch (_shader_type)
  {
  case sge::cg::profile::shader_type::vertex:
    return CG_GL_VERTEX;
  case sge::cg::profile::shader_type::pixel:
    return CG_GL_FRAGMENT;
  case sge::cg::profile::shader_type::geometry:
    return CG_GL_GEOMETRY;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
