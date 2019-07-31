//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/info/name.hpp>
#include <sge/x11input/device/info/name.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::info::name
sge::x11input::device::info::name(
	XIDeviceInfo const &_info
)
{
	return
		sge::input::info::name(
			fcppt::from_std_string(
				_info.name
			)
		);
}
