//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_id.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/sdlinput/keyboard/translate_event.hpp>
#include <sge/sdlinput/translate/key_code.hpp>
#include <sge/sdlinput/translate/pressed.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>


awl::event::optional_base_unique_ptr
sge::sdlinput::keyboard::translate_event(
	sge::input::keyboard::shared_ptr const &_keyboard,
	SDL_KeyboardEvent const &_event
)
{
	return
		fcppt::optional::make_if(
			_event.repeat
			==
			0,
			[
				&_keyboard,
				&_event
			]{
				return
					fcppt::unique_ptr_to_base<
						awl::event::base
					>(
						fcppt::make_unique_ptr<
							sge::input::keyboard::event::key
						>(
							_keyboard,
							sge::input::keyboard::key{
								sge::sdlinput::translate::key_code(
									_event.keysym.sym
								),
								sge::input::keyboard::key_id{
									_event.keysym.scancode
								}
							},
							sge::input::key::pressed{
								sge::sdlinput::translate::pressed(
									_event
								)
							}
						)
					);
			}
		);
}
