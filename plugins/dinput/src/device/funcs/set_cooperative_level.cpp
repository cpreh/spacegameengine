//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/funcs/set_cooperative_level.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <fcppt/text.hpp>


void
sge::dinput::device::funcs::set_cooperative_level(
	IDirectInputDevice8 &_device,
	awl::backends::windows::window::object &_window,
	DWORD const _flags
)
{
	if(
		_device.SetCooperativeLevel(
			_window.hwnd(),
			_flags
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("SetCooperativeLevel() failed!")
		);
}
