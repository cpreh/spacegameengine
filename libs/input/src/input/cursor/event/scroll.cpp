//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_value.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/scroll.hpp>


sge::input::cursor::event::scroll::scroll(
	sge::input::cursor::shared_ptr const _cursor,
	sge::input::cursor::scroll_code const _code,
	sge::input::cursor::scroll_value const _value
)
:
	sge::input::cursor::event::scroll::base{
		_cursor
	},
	code_{
		_code
	},
	value_{
		_value
	}
{
}

sge::input::cursor::event::scroll::~scroll()
{
}

sge::input::cursor::scroll_code
sge::input::cursor::event::scroll::code() const
{
	return
		code_;
}

sge::input::cursor::scroll_value
sge::input::cursor::event::scroll::value() const
{
	return
		value_;
}
