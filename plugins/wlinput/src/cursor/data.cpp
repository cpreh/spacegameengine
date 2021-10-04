//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/wlinput/cursor/data.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/reference_impl.hpp>


sge::wlinput::cursor::data::data(
	fcppt::reference<
		sge::wlinput::cursor::object
	> const _cursor,
	awl::backends::wayland::window::object_ref const _window,
	awl::event::container_reference const _events
)
:
	cursor_{
		_cursor
	},
	window_{
		_window
	},
	events_{
		_events
	},
	position_{}
{
}


