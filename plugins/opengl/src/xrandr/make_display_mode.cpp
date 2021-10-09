//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/make_display_mode.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/dimensions.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

sge::renderer::display_mode::object sge::opengl::xrandr::make_display_mode(
    XRRScreenSize const &_screen_size, sge::opengl::xrandr::refresh_rate const _refresh_rate)
{
  return sge::renderer::display_mode::object{
      sge::renderer::display_mode::pixel_size{sge::renderer::screen_size{
          fcppt::cast::to_unsigned(_screen_size.width),
          fcppt::cast::to_unsigned(_screen_size.height)}},
      sge::renderer::display_mode::optional_dimensions{
          sge::renderer::display_mode::dimensions{sge::renderer::screen_size{
              fcppt::cast::to_unsigned(_screen_size.mwidth),
              fcppt::cast::to_unsigned(_screen_size.mheight)}}},
      sge::renderer::display_mode::optional_refresh_rate{sge::renderer::display_mode::refresh_rate{
          fcppt::cast::to_unsigned(_refresh_rate.get())}}};
}
