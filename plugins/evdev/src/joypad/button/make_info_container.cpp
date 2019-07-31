//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/make_info_container.hpp>
#include <sge/evdev/device/read_bits.hpp>
#include <sge/evdev/joypad/button/info_container.hpp>
#include <sge/evdev/joypad/button/make_info.hpp>
#include <sge/evdev/joypad/button/make_info_container.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::button::info_container
sge::evdev::joypad::button::make_info_container(
	sge::evdev::device::fd const &_fd
)
{
	return
		sge::evdev::device::make_info_container<
			sge::input::joypad::button_id,
			sge::input::joypad::button_info,
			KEY_CNT
		>(
			sge::evdev::device::read_bits<
				KEY_CNT
			>(
				_fd,
				EV_KEY
			),
			&sge::evdev::joypad::button::make_info
		);
}
