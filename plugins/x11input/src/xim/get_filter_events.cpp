//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/xim/context_fwd.hpp>
#include <sge/x11input/xim/get_filter_events.hpp>
#include <sge/x11input/xim/get_ic_values.hpp>
#include <awl/backends/x11/window/event/mask.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


awl::backends::x11::window::event::mask
sge::x11input::xim::get_filter_events(
	sge::x11input::xim::context const &_context
)
{
	// NOLINTNEXTLINE(google-runtime-int)
	long mask{
		0L
	};

	sge::x11input::xim::get_ic_values(
		_context,
		XNFilterEvents,
		&mask,
		nullptr
	);

	return
		awl::backends::x11::window::event::mask{
			mask
		};
}
