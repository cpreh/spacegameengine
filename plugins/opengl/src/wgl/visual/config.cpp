//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/wgl/ext.hpp>
#include <sge/opengl/wgl/extension.hpp>
#include <sge/opengl/wgl/extension_set.hpp>
#include <sge/opengl/wgl/extension_supported.hpp>
#include <sge/opengl/wgl/get_proc_address.hpp>
#include <sge/opengl/wgl/scoped_current_fwd.hpp>
#include <sge/opengl/wgl/visual/config.hpp>
#include <sge/opengl/wgl/visual/optional_pixel_format_types.hpp>
#include <sge/opengl/wgl/visual/pixel_format_types.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace
{

sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format
cast_pixel_format_function(PROC const _function)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_VC_WARNING(4191)
  return sge::opengl::deref_fun_ptr(reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(_function));
  FCPPT_PP_POP_WARNING
}

}

sge::opengl::wgl::visual::config::config(
    sge::opengl::wgl::extension_set const &_extensions, sge::opengl::wgl::scoped_current const &)
    : pixel_format_types_(
          sge::opengl::wgl::extension_supported(
              _extensions, sge::opengl::wgl::extension("WGL_ARB_pixel_format"))
              ? sge::opengl::wgl::visual::optional_pixel_format_types(
                    sge::opengl::wgl::visual::pixel_format_types(
                        sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag(
                            WGL_DRAW_TO_WINDOW_ARB),
                        sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag(
                            WGL_SUPPORT_OPENGL_ARB),
                        sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag(
                            WGL_DOUBLE_BUFFER_ARB),
                        sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag(
                            WGL_PIXEL_TYPE_ARB),
                        sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag(
                            WGL_TYPE_RGBA_ARB),
                        sge::opengl::wgl::visual::pixel_format_types::color_bits_flag(
                            WGL_COLOR_BITS_ARB),
                        sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag(
                            WGL_DEPTH_BITS_ARB),
                        sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag(
                            WGL_STENCIL_BITS_ARB),
                        cast_pixel_format_function(
                            sge::opengl::wgl::get_proc_address("wglChoosePixelFormatARB"))))
          : sge::opengl::wgl::extension_supported(
                _extensions, sge::opengl::wgl::extension("WGL_EXT_pixel_format"))
              ? sge::opengl::wgl::visual::optional_pixel_format_types(
                    sge::opengl::wgl::visual::pixel_format_types(
                        sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag(
                            WGL_DRAW_TO_WINDOW_EXT),
                        sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag(
                            WGL_SUPPORT_OPENGL_EXT),
                        sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag(
                            WGL_DOUBLE_BUFFER_EXT),
                        sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag(
                            WGL_PIXEL_TYPE_EXT),
                        sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag(
                            WGL_TYPE_RGBA_EXT),
                        sge::opengl::wgl::visual::pixel_format_types::color_bits_flag(
                            WGL_COLOR_BITS_EXT),
                        sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag(
                            WGL_DEPTH_BITS_EXT),
                        sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag(
                            WGL_STENCIL_BITS_EXT),
                        cast_pixel_format_function(
                            sge::opengl::wgl::get_proc_address("wglChoosePixelFormatEXT"))))
              : sge::opengl::wgl::visual::optional_pixel_format_types()),
      multi_sample_flag_(
          sge::opengl::wgl::extension_supported(
              _extensions, sge::opengl::wgl::extension("WGL_ARB_multisample"))
              ? sge::opengl::wgl::visual::config::optional_int(WGL_SAMPLE_BUFFERS_ARB)
          : sge::opengl::wgl::extension_supported(
                _extensions, sge::opengl::wgl::extension("WGL_EXT_multisample"))
              ? sge::opengl::wgl::visual::config::optional_int(WGL_SAMPLE_BUFFERS_EXT)
              : sge::opengl::wgl::visual::config::optional_int()),
      srgb_flag_(
          sge::opengl::wgl::extension_supported(
              _extensions, sge::opengl::wgl::extension("WGL_ARB_framebuffer_sRGB"))
              ? sge::opengl::wgl::visual::config::optional_int(WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB)
          : sge::opengl::wgl::extension_supported(
                _extensions, sge::opengl::wgl::extension("WGL_EXT_framebuffer_sRGB"))
              ? sge::opengl::wgl::visual::config::optional_int(WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT)
              : sge::opengl::wgl::visual::config::optional_int())
{
}

sge::opengl::wgl::visual::optional_pixel_format_types
sge::opengl::wgl::visual::config::pixel_format_types() const
{
  return pixel_format_types_;
}

sge::opengl::wgl::visual::config::optional_int
sge::opengl::wgl::visual::config::multi_sample_flag() const
{
  return multi_sample_flag_;
}

sge::opengl::wgl::visual::config::optional_int sge::opengl::wgl::visual::config::srgb_flag() const
{
  return srgb_flag_;
}
