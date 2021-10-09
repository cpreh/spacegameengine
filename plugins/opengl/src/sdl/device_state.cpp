//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/sdl/device_state.hpp>
#include <sge/opengl/sdl/get_window_display_mode.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/fullscreen.hpp>
#include <sge/renderer/display_mode/fullscreen_desktop.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

sge::opengl::sdl::device_state::device_state(
    sge::renderer::display_mode::optional_fullscreen const &_fullscreen,
    sge::window::object_ref const _window)
    : sge::opengl::platform::device_state{},
      window_{
          fcppt::optional::to_exception(
              fcppt::cast::dynamic<awl::backends::sdl::window::object>(_window.get().awl_object()),
              []
              {
                return sge::renderer::exception{
                    FCPPT_TEXT("Widnow passed to sdl::device_state is not an SDL window.")};
              })
              .get()}
{
  this->do_fullscreen(_fullscreen);
}

sge::opengl::sdl::device_state::~device_state() = default;

sge::renderer::display_mode::optional_object sge::opengl::sdl::device_state::display_mode() const
{
  return fcppt::optional::map(
      sge::opengl::sdl::get_window_display_mode(this->window_.get()),
      [](SDL_DisplayMode const &_mode)
      {
        return sge::renderer::display_mode::object{
            sge::renderer::display_mode::pixel_size{sge::renderer::screen_size{
                fcppt::cast::to_unsigned(_mode.w), fcppt::cast::to_unsigned(_mode.h)}},
            sge::renderer::display_mode::optional_dimensions{},
            fcppt::optional::make_if(
                _mode.refresh_rate != 0,
                [&_mode] {
                  return sge::renderer::display_mode::refresh_rate{
                      fcppt::cast::to_unsigned(_mode.refresh_rate)};
                })};
      });
}

void sge::opengl::sdl::device_state::fullscreen(
    sge::renderer::display_mode::optional_fullscreen const &_opt_fullscreen)
{
  this->do_fullscreen(_opt_fullscreen);
}

void sge::opengl::sdl::device_state::do_fullscreen(
    sge::renderer::display_mode::optional_fullscreen const &_opt_fullscreen)
{
  auto const set_fullscreen(
      [this](std::uint32_t const _value)
      {
        if (SDL_SetWindowFullscreen(&this->window_.get().get().get(), _value) == -1)
        {
          throw sge::renderer::exception{FCPPT_TEXT("SDL_SetWindowFullscreen failed!")};
        }
      });

  fcppt::optional::maybe(
      _opt_fullscreen,
      [&set_fullscreen] { set_fullscreen(0); },
      [&set_fullscreen](sge::renderer::display_mode::fullscreen const &_fullscreen)
      {
        fcppt::variant::match(
            _fullscreen,
            [&set_fullscreen](sge::renderer::display_mode::fullscreen_desktop const &)
            { set_fullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP); },
            [&set_fullscreen](sge::renderer::display_mode::object const & /*_display_mode*/
            )
            {
              // TODO(philipp): Set display_mode
              set_fullscreen(SDL_WINDOW_FULLSCREEN);
            });
      });
}
