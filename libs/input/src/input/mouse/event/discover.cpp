//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <sge/input/mouse/event/discover.hpp>


sge::input::mouse::event::discover::discover(
	sge::input::mouse::shared_ptr const _mouse
)
:
	sge::input::mouse::event::base{
		_mouse
	}
{
}

sge::input::mouse::event::discover::~discover()
{
}
