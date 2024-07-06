//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/screen_resources.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xrandr::screen_resources::screen_resources(
    awl::backends::x11::window::const_base_ref const _window)
    : resources_{::XRRGetScreenResources(_window.get().display().get().get(), _window.get().get())}
{
  if (resources_ == nullptr)
  {
    throw sge::renderer::exception{FCPPT_TEXT("XRRGetScreenResources failed")};
  }
}

sge::opengl::xrandr::screen_resources::~screen_resources() { ::XRRFreeScreenResources(resources_); }

XRRScreenResources *sge::opengl::xrandr::screen_resources::get() const { return resources_; }

XRRScreenResources const &sge::opengl::xrandr::screen_resources::get_ref() const
{
  return *resources_;
}
