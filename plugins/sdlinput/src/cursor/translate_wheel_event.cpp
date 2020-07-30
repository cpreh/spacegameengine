//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/scroll.hpp>
#include <sge/sdlinput/cursor/translate_wheel_event.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


awl::event::container
sge::sdlinput::cursor::translate_wheel_event(
	sge::input::cursor::shared_ptr const &_cursor,
	SDL_MouseWheelEvent const &_event
)
{
	awl::event::container result{};

	auto const make_event(
		[
			&result,
			&_cursor
		](
			sge::input::cursor::scroll_code const _code,
			std::int32_t const _value
		)
		{
			if(
				_value
				!=
				0
			)
			{
				result.push_back(
					fcppt::unique_ptr_to_base<
						awl::event::base
					>(
						fcppt::make_unique_ptr<
							sge::input::cursor::event::scroll
						>(
							_cursor,
							_code,
							_value
						)
					)
				);
			}
		}
	);

	make_event(
		sge::input::cursor::scroll_code::horizontal,
		_event.x
	);

	make_event(
		sge::input::cursor::scroll_code::vertical,
		_event.y
	);

	return
		result;
}
