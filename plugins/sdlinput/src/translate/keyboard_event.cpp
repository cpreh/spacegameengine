//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/sdlinput/same_windows.hpp>
#include <sge/sdlinput/focus/translate_keyboard_event.hpp>
#include <sge/sdlinput/keyboard/translate_event.hpp>
#include <sge/sdlinput/translate/keyboard_event.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/not.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <vector>
#include <fcppt/config/external_end.hpp>

awl::event::container sge::sdlinput::translate::keyboard_event(
    sge::input::focus::shared_ptr const &_focus,
    sge::input::keyboard::shared_ptr const &_keyboard,
    awl::backends::sdl::window::object const &_window,
    SDL_KeyboardEvent const &_event)
{
  if (fcppt::not_(sge::sdlinput::same_windows(_window, _event)))
  {
    return awl::event::container{};
  }

  return fcppt::optional::cat<awl::event::container>(
      fcppt::container::make<std::vector<awl::event::optional_base_unique_ptr>>(
          sge::sdlinput::keyboard::translate_event(_keyboard, _event),
          awl::event::optional_base_unique_ptr{
              sge::sdlinput::focus::translate_keyboard_event(_focus, _event)}));
}
