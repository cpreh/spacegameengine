//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/focus/object.hpp>
#include <sge/sdlinput/focus/object.hpp>
#include <sge/window/object_fwd.hpp>


sge::sdlinput::focus::object::object(
	sge::window::object &_window
)
:
	sge::input::focus::object{},
	window_{
		_window
	}
{
}

sge::sdlinput::focus::object::~object()
{
}

sge::window::object &
sge::sdlinput::focus::object::window() const
{
	return
		this->window_;
}
