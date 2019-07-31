//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/discover.hpp>


sge::input::cursor::event::discover::discover(
	sge::input::cursor::shared_ptr const _cursor
)
:
	sge::input::cursor::event::base{
		_cursor
	}
{
}

sge::input::cursor::event::discover::~discover()
{
}
