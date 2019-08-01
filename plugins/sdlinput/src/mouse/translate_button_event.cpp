//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/button.hpp>
#include <sge/sdlinput/mouse/translate_button_code.hpp>
#include <sge/sdlinput/mouse/translate_button_event.hpp>
#include <sge/sdlinput/translate/pressed.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>


awl::event::base_unique_ptr
sge::sdlinput::mouse::translate_button_event(
	sge::input::mouse::shared_ptr const &_mouse,
	SDL_MouseButtonEvent const &_event
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::mouse::event::button
			>(
				_mouse,
				sge::input::mouse::button{
					sge::sdlinput::mouse::translate_button_code(
						_event.button
					),
					sge::input::mouse::button_id{
						_event.button
					}
				},
				sge::input::mouse::button_pressed{
					sge::sdlinput::translate::pressed(
						_event
					)
				}
			)
		);
}
