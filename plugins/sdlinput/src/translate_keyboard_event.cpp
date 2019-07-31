//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/sdlinput/same_windows.hpp>
#include <sge/sdlinput/translate_keyboard_event.hpp>
#include <fcppt/not.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>


awl::event::container
sge::sdlinput::translate_keyboard_event(
	sge::input::focus::shared_ptr const &_focus,
	sge::input::keyboard::shared_ptr const &_keyboard,
	awl::backends::sdl::window::object const &_window,
	SDL_KeyboardEvent const &_event
)
{
	if(
		fcppt::not_(
			sge::sdlinput::same_windows(
				_window,
				_event
			)
		)
	)
		return
			awl::event::container{};

	// TODO
	return
		awl::event::container{};
}
