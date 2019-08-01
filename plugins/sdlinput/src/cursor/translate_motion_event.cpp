//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/sdlinput/cursor/translate_motion_event.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>


awl::event::base_unique_ptr
sge::sdlinput::cursor::translate_motion_event(
	sge::input::cursor::shared_ptr const &_cursor,
	SDL_MouseMotionEvent const &_event
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::cursor::event::move
			>(
				_cursor,
				sge::input::cursor::optional_position{
					sge::input::cursor::position{
						_event.x,
						_event.y
					}
				}
			)
		);
}
