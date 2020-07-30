//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/keyboard/device.hpp>
#include <sge/sdlinput/keyboard/device.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>


sge::sdlinput::keyboard::device::device(
	sge::window::object_ref const _window
)
:
	sge::input::keyboard::device{},
	window_{
		_window
	}
{
}

sge::sdlinput::keyboard::device::~device()
= default;

sge::window::object &
sge::sdlinput::keyboard::device::window() const
{
	return
		this->window_.get();
}
