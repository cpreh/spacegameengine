//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/windows/current_display_mode.hpp>
#include <sge/opengl/windows/enum_display_settings.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/backends/windows/windows.hpp>

sge::renderer::display_mode::object const sge::opengl::windows::current_display_mode()
{
  DEVMODE const mode(sge::opengl::windows::enum_display_settings(nullptr, ENUM_CURRENT_SETTINGS));

  return sge::renderer::display_mode::object(
      sge::renderer::display_mode::pixel_size(
          sge::renderer::screen_size(mode.dmPelsWidth, mode.dmPelsHeight)),
      sge::renderer::display_mode::optional_dimensions(),
      sge::renderer::display_mode::optional_refresh_rate(
          sge::renderer::display_mode::refresh_rate(mode.dmDisplayFrequency)));
}
