//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/sdlinput/cursor/object.hpp>


sge::sdlinput::cursor::object::object(
	sge::window::object &_window
)
:
	sge::input::cursor::object{},
	window_{
		_window
	}
{
}

sge::sdlinput::cursor::object::~object()
{
}

sge::window::object &
sge::sdlinput::cursor::object::window() const
{
	return
		this->window_;
}

sge::input::cursor::optional_position
sge::sdlinput::cursor::object::position() const
{
	// TODO
	return
		sge::input::cursor::optional_position{};
}

void
sge::sdlinput::cursor::object::mode(
	sge::input::cursor::mode const _mode
)
{
}
