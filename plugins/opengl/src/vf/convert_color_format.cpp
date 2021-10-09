//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/format.hpp>
#include <sge/opengl/vf/color_formats.hpp>
#include <sge/opengl/vf/convert_color_format.hpp>
#include <sge/renderer/vf/dynamic/matching_color_format.hpp>

sge::image::color::format
sge::opengl::vf::convert_color_format(sge::image::color::format const _format)
{
  return sge::renderer::vf::dynamic::matching_color_format(
      _format, sge::opengl::vf::color_formats());
}
