//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/const_configuration_ref.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/optional_refresh_rate.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/rotation.hpp>
#include <sge/opengl/xrandr/set_resolution.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/randr.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xrandr::resolution::resolution(
    awl::backends::x11::window::const_base_ref const _window,
    sge::opengl::xrandr::const_configuration_ref const _config,
    sge::opengl::xrandr::mode_index const _mode_index,
    sge::renderer::display_mode::optional_refresh_rate const &_opt_rate,
    sge::opengl::xrandr::mode const &_old_mode)
    : window_{_window}, config_{_config}, old_mode_{_old_mode}
{
  sge::opengl::xrandr::set_resolution(
      window_.get(),
      config_.get(),
      _mode_index,
      sge::opengl::xrandr::rotation{fcppt::cast::size<unsigned short // NOLINT(google-runtime-int)
                                                      >(fcppt::cast::to_unsigned(RR_Rotate_0))},
      fcppt::optional::map(
          _opt_rate,
          [](sge::renderer::display_mode::refresh_rate const _rate)
          {
            return fcppt::strong_typedef_construct_cast<
                sge::opengl::xrandr::refresh_rate,
                fcppt::cast::size_fun>(fcppt::cast::to_signed(_rate.get()));
          }));
}

sge::opengl::xrandr::resolution::~resolution()
{
  sge::opengl::xrandr::set_resolution(
      window_.get(),
      config_.get(),
      old_mode_.index(),
      old_mode_.rotation(),
      sge::opengl::xrandr::optional_refresh_rate(old_mode_.rate()));
}
