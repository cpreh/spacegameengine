//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/convert/depth_stencil_base_type.hpp>
#include <sge/opengl/convert/make_color_base_type.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::opengl::color_base_type
sge::opengl::convert::depth_stencil_base_type(sge::image::ds::format const _type)
{
  switch (_type)
  {
  case sge::image::ds::format::d16:
    return sge::opengl::convert::make_color_base_type<GL_UNSIGNED_SHORT>();
  case sge::image::ds::format::d32:
  case sge::image::ds::format::d24s8:
    return sge::opengl::convert::make_color_base_type<GL_FLOAT>();
  }

  FCPPT_ASSERT_UNREACHABLE;
}
