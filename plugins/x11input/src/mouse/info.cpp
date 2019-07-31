//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/info.hpp>
#include <sge/x11input/device/info/name.hpp>
#include <sge/x11input/mouse/info.hpp>
#include <sge/x11input/mouse/make_axis_infos.hpp>
#include <sge/x11input/mouse/make_button_infos.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::info
sge::x11input::mouse::info(
	awl::backends::x11::display &_display,
	XIDeviceInfo const &_info
)
{
	return
		sge::input::mouse::info(
			sge::x11input::mouse::make_axis_infos(
				_display,
				_info
			),
			sge::x11input::mouse::make_button_infos(
				_display,
				_info
			),
			sge::x11input::device::info::name(
				_info
			)
		);
}
