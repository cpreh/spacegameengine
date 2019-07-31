//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/make_info_container.hpp>
#include <sge/evdev/device/read_bits.hpp>
#include <sge/evdev/joypad/relative_axis/info_container.hpp>
#include <sge/evdev/joypad/relative_axis/make_info.hpp>
#include <sge/evdev/joypad/relative_axis/make_info_container.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::relative_axis::info_container
sge::evdev::joypad::relative_axis::make_info_container(
	sge::evdev::device::fd const &_fd
)
{
	return
		sge::evdev::device::make_info_container<
			sge::input::joypad::relative_axis_id,
			sge::input::joypad::relative_axis_info,
			REL_CNT
		>(
			sge::evdev::device::read_bits<
				REL_CNT
			>(
				_fd,
				EV_REL
			),
			&sge::evdev::joypad::relative_axis::make_info
		);
}
