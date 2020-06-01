//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
				// TODO(philipp): What to put here?
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
								// TODO(philipp): What to put here?
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
