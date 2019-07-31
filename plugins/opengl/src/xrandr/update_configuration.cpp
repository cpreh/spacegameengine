//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/update_configuration.hpp>
#include <awl/backends/x11/window/event/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


bool
sge::opengl::xrandr::update_configuration(
	awl::backends::x11::window::event::object const &_event
)
{
	return
		::XRRUpdateConfiguration(
			const_cast<
				XEvent *
			>(
				&_event.get()
			)
		)
		==
		1;
}
