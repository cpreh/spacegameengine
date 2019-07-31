//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/input/focus/event/out.hpp>


sge::input::focus::event::out::out(
	sge::input::focus::shared_ptr const _focus
)
:
	sge::input::focus::event::base{
		_focus
	}
{
}

sge::input::focus::event::out::~out()
{
}
