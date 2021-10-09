//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/sdlinput/focus/translate_keyboard_event.hpp>
#include <sge/sdlinput/translate/key_code.hpp>
#include <sge/sdlinput/translate/pressed.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>

awl::event::base_unique_ptr sge::sdlinput::focus::translate_keyboard_event(
    sge::input::focus::shared_ptr const &_focus, SDL_KeyboardEvent const &_event)
{
  sge::input::focus::key const key{sge::sdlinput::translate::key_code(_event.keysym.sym)};

  return _event.repeat == 0
             ? fcppt::unique_ptr_to_base<awl::event::base>(
                   fcppt::make_unique_ptr<sge::input::focus::event::key>(
                       _focus,
                       key,
                       sge::input::key::pressed{sge::sdlinput::translate::pressed(_event)}))
             : fcppt::unique_ptr_to_base<awl::event::base>(
                   fcppt::make_unique_ptr<sge::input::focus::event::key_repeat>(_focus, key));
}
