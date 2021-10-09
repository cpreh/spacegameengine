//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/text.hpp>
#include <sge/sdlinput/same_windows.hpp>
#include <sge/sdlinput/focus/translate_text_event.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/not.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/widen.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <string>
#include <fcppt/config/external_end.hpp>

awl::event::container sge::sdlinput::focus::translate_text_event(
    sge::input::focus::shared_ptr const &_focus,
    awl::backends::sdl::window::object const &_window,
    SDL_TextInputEvent const &_event)
{
  if (fcppt::not_(sge::sdlinput::same_windows(_window, _event)))
  {
    return awl::event::container{};
  }

  return fcppt::container::make<awl::event::container>(fcppt::unique_ptr_to_base<awl::event::base>(
      fcppt::make_unique_ptr<sge::input::focus::event::text>(
          _focus, fcppt::widen(std::string{std::data(_event.text)}))));
}
