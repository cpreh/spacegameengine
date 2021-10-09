//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/wgl/visual/pixel_format_types.hpp>

sge::opengl::wgl::visual::pixel_format_types::pixel_format_types(
    sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag const _draw_to_window,
    sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag const _support_opengl,
    sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag const _double_buffer,
    sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag const _pixel_type,
    sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag const _pixel_type_rgba,
    sge::opengl::wgl::visual::pixel_format_types::color_bits_flag const _color_bits,
    sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag const _depth_bits,
    sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag const _stencil_bits,
    sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format const
        _choose_pixel_format)
    : draw_to_window_(_draw_to_window),
      support_opengl_(_support_opengl),
      double_buffer_(_double_buffer),
      pixel_type_(_pixel_type),
      pixel_type_rgba_(_pixel_type_rgba),
      color_bits_(_color_bits),
      depth_bits_(_depth_bits),
      stencil_bits_(_stencil_bits),
      choose_pixel_format_(_choose_pixel_format)
{
}

sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag
sge::opengl::wgl::visual::pixel_format_types::draw_to_window() const
{
  return draw_to_window_;
}

sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag
sge::opengl::wgl::visual::pixel_format_types::support_opengl() const
{
  return support_opengl_;
}

sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag
sge::opengl::wgl::visual::pixel_format_types::double_buffer() const
{
  return double_buffer_;
}

sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag
sge::opengl::wgl::visual::pixel_format_types::pixel_type() const
{
  return pixel_type_;
}

sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag
sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba() const
{
  return pixel_type_rgba_;
}

sge::opengl::wgl::visual::pixel_format_types::color_bits_flag
sge::opengl::wgl::visual::pixel_format_types::color_bits() const
{
  return color_bits_;
}

sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag
sge::opengl::wgl::visual::pixel_format_types::depth_bits() const
{
  return depth_bits_;
}

sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag
sge::opengl::wgl::visual::pixel_format_types::stencil_bits() const
{
  return stencil_bits_;
}

sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format
sge::opengl::wgl::visual::pixel_format_types::choose_pixel_format() const
{
  return choose_pixel_format_;
}
