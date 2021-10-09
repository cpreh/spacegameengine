//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/parameters/create.hpp>
#include <sge/d3d9/parameters/extract_size.hpp>
#include <sge/d3d9/parameters/convert/bit_depth.hpp>
#include <sge/d3d9/parameters/convert/depth_stencil_buffer.hpp>
#include <sge/d3d9/parameters/convert/multi_sample.hpp>
#include <sge/d3d9/parameters/convert/multi_sample_quality.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/display_mode/fullscreen.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/window/object.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/to_optional.hpp>

D3DPRESENT_PARAMETERS
sge::d3d9::parameters::create(
    sge::renderer::pixel_format::object const &_pixel_format,
    sge::renderer::display_mode::parameters const &_parameters,
    awl::window::object &_window)
{
  sge::renderer::screen_size const back_buffer_size(sge::d3d9::parameters::extract_size(
      fcppt::optional::bind(
          _parameters.fullscreen(),
          [](sge::renderer::display_mode::fullscreen const &_fullscreen) {
            return fcppt::variant::to_optional<sge::renderer::display_mode::object>(_fullscreen);
          }),
      _window));

  bool const has_depth_stencil(
      _pixel_format.depth_stencil() != sge::renderer::pixel_format::depth_stencil::off);

  D3DPRESENT_PARAMETERS const ret = {
      back_buffer_size.w(), // BackBufferWidth
      back_buffer_size.h(), // BackBufferHeight
      sge::d3d9::parameters::convert::bit_depth(_pixel_format.color()), // BackBufferFormat
      1u, // BackBufferCount,
      sge::d3d9::parameters::convert::multi_sample(_pixel_format.multi_samples()),
      sge::d3d9::parameters::convert::multi_sample_quality(_pixel_format.multi_samples()),
      D3DSWAPEFFECT_DISCARD, // SwapEffect
      fcppt::optional::to_exception(
          fcppt::cast::dynamic<awl::backends::windows::window::object>(_window),
          []
          {
            return sge::renderer::exception{
                FCPPT_TEXT("Window passed to d3d9::parameters::create is not a Windows window.")};
          })
          ->hwnd(), // hDeviceWindow
      !_parameters.fullscreen().has_value(), // Windowed
      has_depth_stencil, // EnableAutoDepthStencil
      sge::d3d9::parameters::convert::depth_stencil_buffer(
          _pixel_format.depth_stencil()), // AutoDepthStencilFormat
      has_depth_stencil ? D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL : 0u, // Flags
      // FullScreen_RefreshRateInHz
      fcppt::optional::maybe(
          fcppt::optional::bind(
              _parameters.fullscreen(),
              [](sge::renderer::display_mode::fullscreen const &_fullscreen)
                  -> sge::renderer::display_mode::optional_refresh_rate
              {
                return fcppt::optional::join(fcppt::optional::map(
                    fcppt::variant::to_optional<sge::renderer::display_mode::object>(_fullscreen),
                    [](sge::renderer::display_mode::object const &_display_mode)
                    { return _display_mode.refresh_rate(); }));
              }),
          fcppt::const_(0u),
          [](sge::renderer::display_mode::refresh_rate const _refresh_rate)
          { return _refresh_rate.get(); }),
      _parameters.vsync() == sge::renderer::display_mode::vsync::on
          ? D3DPRESENT_INTERVAL_ONE
          : D3DPRESENT_INTERVAL_IMMEDIATE // PresentationInterval
  };

  return ret;
}
