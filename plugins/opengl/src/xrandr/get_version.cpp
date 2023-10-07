//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/extension_fwd.hpp>
#include <sge/opengl/xrandr/get_version.hpp>
#include <sge/opengl/xrandr/version.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xrandr::version sge::opengl::xrandr::get_version(
    sge::opengl::xrandr::extension const &, awl::backends::x11::display_ref const _display)
{
  int major{};

  int minor{};

  if (::XRRQueryVersion(_display.get().get(), &major, &minor) != 1)
  {
    throw sge::renderer::exception(FCPPT_TEXT("Querying the xrandr version failed!"));
  }

  return sge::opengl::xrandr::version{
      sge::opengl::xrandr::version::major_type{major},
      sge::opengl::xrandr::version::minor_type{minor}};
}
