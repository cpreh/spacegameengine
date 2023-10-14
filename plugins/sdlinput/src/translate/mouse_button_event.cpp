//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/sdlinput/same_windows.hpp>
#include <sge/sdlinput/cursor/translate_button_event.hpp>
#include <sge/sdlinput/mouse/translate_button_event.hpp>
#include <sge/sdlinput/translate/mouse_button_event.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/event/container.hpp>
#include <fcppt/not.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>

awl::event::container sge::sdlinput::translate::mouse_button_event(
    sge::input::cursor::shared_ptr const &_cursor,
    sge::input::mouse::shared_ptr const &_mouse,
    awl::backends::sdl::window::object const &_window,
    SDL_MouseButtonEvent const &_event)
{
  if (fcppt::not_(sge::sdlinput::same_windows(_window, _event)))
  {
    return awl::event::container{};
  }

  return fcppt::container::make<awl::event::container>(
      sge::sdlinput::mouse::translate_button_event(_mouse, _event),
      sge::sdlinput::cursor::translate_button_event(_cursor, _event));
}
