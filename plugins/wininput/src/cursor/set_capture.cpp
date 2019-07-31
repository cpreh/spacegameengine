//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/wininput/cursor/set_capture.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/object.hpp>


void
sge::wininput::cursor::set_capture(
	awl::backends::windows::window::object &_window
)
{
	::SetCapture(
		_window.hwnd()
	);
}
