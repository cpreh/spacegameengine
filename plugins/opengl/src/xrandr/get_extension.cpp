//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/get_extension.hpp>
#include <sge/opengl/xrandr/optional_extension.hpp>
#include <awl/backends/x11/display.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xrandr::optional_extension
sge::opengl::xrandr::get_extension(awl::backends::x11::display_ref const _display)
{
  int event_base_return{};

  int error_base_return{};

  return ::XRRQueryExtension(_display.get().get(), &event_base_return, &error_base_return) == False
             ? sge::opengl::xrandr::optional_extension()
             : sge::opengl::xrandr::optional_extension(sge::opengl::xrandr::extension(
                   sge::opengl::xrandr::extension::event_base_type(event_base_return)));
}
