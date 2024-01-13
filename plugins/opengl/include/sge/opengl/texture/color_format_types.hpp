//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_COLOR_FORMAT_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_COLOR_FORMAT_TYPES_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/opengl/color_format_fwd.hpp>
#include <sge/opengl/texture/color_format_types_fwd.hpp> // IWYU pragma: keep
#include <sge/opengl/texture/convert_base_type_function.hpp>
#include <sge/opengl/texture/convert_internal_format_function.hpp>
#include <sge/opengl/texture/convert_order_function.hpp>
#include <sge/opengl/texture/format_result_fwd.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>

namespace sge::opengl::texture
{

struct color_format_types
{
  using format = sge::image::color::format;

  using gl_format = sge::opengl::color_format;

  using convert_order_function_type = sge::opengl::texture::convert_order_function<gl_format>;

  [[nodiscard]] static convert_order_function_type convert_order();

  using convert_base_type_function = sge::opengl::texture::convert_base_type_function<gl_format>;

  [[nodiscard]] static convert_base_type_function convert_base_type();

  using convert_internal_format_function =
      sge::opengl::texture::convert_internal_format_function<gl_format>;

  [[nodiscard]] static convert_internal_format_function convert_internal_format();

  using format_result = sge::opengl::texture::format_result<format, gl_format>;

  [[nodiscard]] static format_result translate_format(sge::renderer::texture::color_format const &);
};

}

#endif
