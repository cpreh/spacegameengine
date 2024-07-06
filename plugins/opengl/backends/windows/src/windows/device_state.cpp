//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/opengl/windows/current_display_mode.hpp>
#include <sge/opengl/windows/device_state.hpp>
#include <sge/renderer/display_mode/fullscreen.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/to_optional.hpp>

sge::opengl::windows::device_state::device_state(
    fcppt::log::object &_log, sge::renderer::display_mode::optional_fullscreen const &_fullscreen)
    : sge::opengl::platform::device_state(), log_{_log}
{
  this->fullscreen(_fullscreen);
}

sge::opengl::windows::device_state::~device_state() {}

sge::renderer::display_mode::optional_object
sge::opengl::windows::device_state::display_mode() const
{
  // TODO
  return sge::renderer::display_mode::optional_object(sge::opengl::windows::current_display_mode());
}

void sge::opengl::windows::device_state::fullscreen(
    sge::renderer::display_mode::optional_fullscreen const &_opt_fullscreen)
{
  // FIXME: Change mode back
  fcppt::optional::maybe_void(
      _opt_fullscreen,
      [this](sge::renderer::display_mode::fullscreen const &_fullscreen)
      {
        // TODO: Make window borderless
        fcppt::optional::maybe_void(
            fcppt::variant::to_optional<sge::renderer::display_mode::object>(_fullscreen),
            [this](sge::renderer::display_mode::object const &_display_mode)
            { sge::opengl::windows::change_display_settings(this->log_, _display_mode); });
      });
}
