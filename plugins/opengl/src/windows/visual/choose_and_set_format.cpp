//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/wgl/visual/choose_format.hpp>
#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/windows/visual/choose_and_set_format.hpp>
#include <sge/opengl/windows/visual/choose_format.hpp>
#include <sge/opengl/windows/visual/make_format.hpp>
#include <sge/opengl/windows/visual/set_format.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <awl/backends/windows/windows.hpp>

void sge::opengl::windows::visual::choose_and_set_format(
    sge::opengl::wgl::visual::config const &_config,
    HWND const _hwnd,
    sge::renderer::pixel_format::object const &_pixel_format)
{
  sge::opengl::windows::gdi_device const device(_hwnd, sge::opengl::windows::gdi_device::get_tag());

  bool const needs_wgl(
      _pixel_format.multi_samples().has_value() ||
      _pixel_format.srgb() == sge::renderer::pixel_format::srgb::yes);

  PIXELFORMATDESCRIPTOR const format_desc(sge::opengl::windows::visual::make_format(
      _pixel_format.color(), _pixel_format.depth_stencil()));

  sge::opengl::windows::visual::set_format(
      device,
      needs_wgl ? sge::opengl::wgl::visual::choose_format(device, _config, _pixel_format)
                : sge::opengl::windows::visual::choose_format(device, format_desc),
      format_desc);
}
