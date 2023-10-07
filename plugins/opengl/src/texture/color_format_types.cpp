//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/convert/color_base_type.hpp>
#include <sge/opengl/convert/color_format.hpp>
#include <sge/opengl/convert/color_order.hpp>
#include <sge/opengl/convert/internal_color_format.hpp>
#include <sge/opengl/texture/best_color_format.hpp>
#include <sge/opengl/texture/color_format_types.hpp>
#include <sge/opengl/texture/format_result_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/translate_srgb_emulation.hpp>

sge::opengl::texture::color_format_types::convert_order_function_type
sge::opengl::texture::color_format_types::convert_order()
{
  return sge::opengl::convert::color_order;
}

sge::opengl::texture::color_format_types::convert_base_type_function
sge::opengl::texture::color_format_types::convert_base_type()
{
  return sge::opengl::convert::color_base_type;
}

sge::opengl::texture::color_format_types::convert_internal_format_function
sge::opengl::texture::color_format_types::convert_internal_format()
{
  return sge::opengl::convert::internal_color_format;
}

sge::opengl::texture::color_format_types::format_result
sge::opengl::texture::color_format_types::translate_format(
    sge::renderer::texture::color_format const &_format)
{
  format const best_format{sge::opengl::convert::color_format(
      sge::opengl::texture::best_color_format(_format.format()))};

  return sge::opengl::texture::color_format_types::format_result{
      best_format,
      sge::opengl::texture::best_color_format(sge::renderer::texture::translate_srgb_emulation(
          sge::renderer::texture::color_format(best_format, _format.emulate_srgb())))};
}
