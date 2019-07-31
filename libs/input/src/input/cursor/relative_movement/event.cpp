//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/relative_movement/difference.hpp>
#include <sge/input/cursor/relative_movement/event.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::relative_movement::event::event(
	sge::input::cursor::shared_ptr _cursor,
	sge::input::cursor::relative_movement::difference const _difference
)
:
	sge::input::cursor::event::base{
		std::move(
			_cursor
		)
	},
	difference_{
		_difference
	}
{
}

sge::input::cursor::relative_movement::event::~event()
{
}

sge::input::cursor::relative_movement::difference
sge::input::cursor::relative_movement::event::difference() const
{
	return
		difference_;
}
