//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/in.hpp>
#include <sge/input/focus/event/out.hpp>
#include <sge/sdlinput/same_windows.hpp>
#include <sge/sdlinput/cursor/get_position.hpp>
#include <sge/sdlinput/translate/window_event.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/not.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>

awl::event::container sge::sdlinput::translate::window_event(
    sge::input::cursor::shared_ptr const &_cursor,
    sge::input::focus::shared_ptr const &_focus,
    awl::backends::sdl::window::object const &_window,
    SDL_WindowEvent const &_event)
{
  if (fcppt::not_(sge::sdlinput::same_windows(_window, _event)))
  {
    return awl::event::container{};
  }

  switch (_event.event)
  {
  case SDL_WINDOWEVENT_ENTER:
    return fcppt::container::make<awl::event::container>(
        fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::cursor::event::move>(
                _cursor,
                sge::input::cursor::optional_position{sge::sdlinput::cursor::get_position()})));
  case SDL_WINDOWEVENT_LEAVE:
    return fcppt::container::make<awl::event::container>(
        fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::cursor::event::move>(
                _cursor, sge::input::cursor::optional_position())));
  case SDL_WINDOWEVENT_FOCUS_GAINED:
    return fcppt::container::make<awl::event::container>(
        fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::focus::event::in>(_focus)));
  case SDL_WINDOWEVENT_FOCUS_LOST:
    return fcppt::container::make<awl::event::container>(
        fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::focus::event::out>(_focus)));
  default: break;
  }

  return awl::event::container{};
}
