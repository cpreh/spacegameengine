//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/input_mask.hpp>
#include <sge/opengl/xrandr/select_input.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


void
sge::opengl::xrandr::select_input(
	awl::backends::x11::window::base const &_window,
	sge::opengl::xrandr::input_mask const _mask
)
{
	::XRRSelectInput(
		_window.display().get().get(),
		_window.get(),
		_mask.get()
	);
}
