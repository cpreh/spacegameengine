//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/window/object_ref.hpp>

sge::renderer::device::parameters::parameters(
    sge::renderer::display_mode::parameters const _display_mode,
    sge::window::object_ref const _window)
    : display_mode_{_display_mode}, window_{_window}
{
}

sge::renderer::display_mode::parameters const &
sge::renderer::device::parameters::display_mode() const
{
  return display_mode_;
}

sge::window::object_ref sge::renderer::device::parameters::window() const { return window_; }
