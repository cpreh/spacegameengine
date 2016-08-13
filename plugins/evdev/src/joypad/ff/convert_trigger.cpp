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


#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/convert_duration.hpp>
#include <sge/evdev/joypad/ff/convert_trigger.hpp>
#include <sge/evdev/joypad/ff/find_button.hpp>
#include <sge/input/joypad/ff/duration.hpp>
#include <sge/input/joypad/ff/optional_trigger_fwd.hpp>
#include <sge/input/joypad/ff/trigger.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


ff_trigger
sge::evdev::joypad::ff::convert_trigger(
	sge::evdev::joypad::button::event_map const &_buttons,
	sge::input::joypad::ff::optional_trigger const &_opt_trigger
)
{
	return
		fcppt::optional::maybe(
			_opt_trigger,
			[]{
				// TODO: What to put here?
				return
					ff_trigger{
						fcppt::literal<
							std::uint16_t
						>(
							0
						),
						fcppt::literal<
							std::uint16_t
						>(
							0
						)
					};
			},
			[
				&_buttons
			](
				sge::input::joypad::ff::trigger const &_trigger
			){
				return
					ff_trigger{
						sge::evdev::joypad::ff::find_button(
							_buttons,
							_trigger.button()
						).get(),
						fcppt::optional::maybe(
							_trigger.cooldown().get(),
							[]{
								// TODO: What to put here?
								return
									fcppt::literal<
										std::uint16_t
									>(
										0
									);
							},
							[](
								sge::input::joypad::ff::duration const _duration
							)
							{
								return
									sge::evdev::joypad::ff::convert_duration(
										_duration
									);
							}
						)
					};
			}
		);
}
