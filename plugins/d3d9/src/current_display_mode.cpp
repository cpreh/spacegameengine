//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/current_display_mode.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/get_display_mode.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>

sge::renderer::display_mode::object const sge::d3d9::current_display_mode(IDirect3DDevice9 &_device)
{
  D3DDISPLAYMODE const mode(sge::d3d9::devicefuncs::get_display_mode(_device, 0u));

  return sge::renderer::display_mode::object(
      sge::renderer::display_mode::pixel_size(sge::renderer::screen_size(mode.Width, mode.Height)),
      sge::renderer::display_mode::optional_dimensions(),
      sge::renderer::display_mode::optional_refresh_rate(
          sge::renderer::display_mode::refresh_rate(mode.RefreshRate)));
}
