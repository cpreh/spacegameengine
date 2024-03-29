//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xrandr::configuration::configuration(
    awl::backends::x11::window::const_base_ref const _window)
    : config_{::XRRGetScreenInfo(_window.get().display().get().get(), _window.get().get())}
{
  if (config_ == nullptr)
  {
    throw sge::renderer::exception{FCPPT_TEXT("XRRGetScreenInfo failed")};
  }
}

::XRRScreenConfiguration *sge::opengl::xrandr::configuration::get() const { return config_; }

sge::opengl::xrandr::configuration::~configuration() { ::XRRFreeScreenConfigInfo(config_); }
