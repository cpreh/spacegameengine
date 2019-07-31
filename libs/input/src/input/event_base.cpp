//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/event_base.hpp>
#include <sge/window/object.hpp>
#include <awl/window/reference.hpp>
#include <awl/window/event/base.hpp>


sge::input::event_base::event_base(
	sge::window::object const &_window
)
:
	awl::window::event::base{
		awl::window::reference{
			_window.awl_object()
		}
	}
{
}

sge::input::event_base::~event_base()
{
}
