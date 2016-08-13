/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/is_joypad.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <fcppt/loop.hpp>
#include <fcppt/algorithm/fold_break.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


bool
sge::evdev::joypad::is_joypad(
	sge::evdev::joypad::info const &_info
)
{
	return
		fcppt::algorithm::fold_break(
			_info.event_map().buttons(),
			false,
			[](
				std::pair<
					sge::evdev::device::event_type,
					sge::input::joypad::button_id
				> const _element,
				bool const _has_joypad_buttons
			)
			{
				int const value(
					fcppt::cast::to_signed(
						_element.first.get()
					)
				);

				if(
					value
					>= BTN_MOUSE
					&&
					value
					<= BTN_TASK
				)
					return
						std::make_pair(
							fcppt::loop::break_,
							false
						);

				if(
					value
					>= BTN_JOYSTICK
					&&
					value
					< BTN_DIGI
				)
					return
						std::make_pair(
							fcppt::loop::continue_,
							true
						);

				return
					std::make_pair(
						fcppt::loop::continue_,
						_has_joypad_buttons
					);
			}
		);
}
