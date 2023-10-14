//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/sdlinput/cursor/get_focus.hpp>
#include <sge/sdlinput/cursor/get_position.hpp>
#include <sge/sdlinput/cursor/object.hpp>
#include <sge/sdlinput/cursor/set_mode.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/window/object.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/sdl/window/object_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>

sge::sdlinput::cursor::object::object(
    sge::window::object_ref const _window, awl::backends::sdl::window::object_ref const _sdl_window)
    : sge::input::cursor::object{}, window_{_window}, sdl_window_{_sdl_window}
{
}

sge::sdlinput::cursor::object::~object() = default;

sge::window::object &sge::sdlinput::cursor::object::window() const { return this->window_.get(); }

sge::input::cursor::optional_position sge::sdlinput::cursor::object::position() const
{
  return fcppt::optional::bind(
      sge::sdlinput::cursor::get_focus(),
      [this](fcppt::reference<SDL_Window> const _window)
      {
        return fcppt::optional::make_if(
            &_window.get() == &this->sdl_window_.get().get().get(),
            [] { return sge::sdlinput::cursor::get_position(); });
      });
}

void sge::sdlinput::cursor::object::mode(sge::input::cursor::mode const _mode)
{
  sge::sdlinput::cursor::set_mode(_mode);
}
