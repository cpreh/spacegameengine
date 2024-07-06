//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/wayland/device_state.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>

sge::opengl::wayland::device_state::device_state(
    sge::renderer::display_mode::optional_fullscreen const &_fullscreen)
    : sge::opengl::platform::device_state()
{
  this->do_fullscreen(_fullscreen);
}

sge::opengl::wayland::device_state::~device_state() = default;

sge::renderer::display_mode::optional_object
sge::opengl::wayland::device_state::display_mode() const
{
  // FIXME
  return sge::renderer::display_mode::optional_object{};
}

void sge::opengl::wayland::device_state::fullscreen(
    sge::renderer::display_mode::optional_fullscreen const &_fullscreen)
{
  this->do_fullscreen(_fullscreen);
}

void sge::opengl::wayland::device_state::do_fullscreen(
    sge::renderer::display_mode::optional_fullscreen const &_fullscreen)
{
}
