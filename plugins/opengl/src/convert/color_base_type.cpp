//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/convert/color_base_type.hpp>
#include <sge/opengl/convert/color_base_type_sge.hpp>
#include <sge/opengl/convert/color_format.hpp>

sge::opengl::color_base_type
sge::opengl::convert::color_base_type(sge::opengl::color_format const _format)
{
  return sge::opengl::convert::color_base_type_sge(sge::opengl::convert::color_format(_format));
}
