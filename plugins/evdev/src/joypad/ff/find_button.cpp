//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/find_button.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::evdev::device::event_type
sge::evdev::joypad::ff::find_button(
	sge::evdev::joypad::button::event_map const &_buttons,
	sge::input::joypad::button_id const _id
)
{
	// TODO(philipp): Use a bimap here?
	return
		fcppt::optional::to_exception(
			fcppt::optional::deref(
				fcppt::algorithm::find_if_opt(
					_buttons,
					[
						_id
					](
						std::pair<
							sge::evdev::device::event_type,
							sge::input::joypad::button_id
						> const _pair
					)
					{
						return
							_pair.second
							==
							_id;
					}
				)
			),
			[
				_id
			]{
				return
					sge::input::exception{
						FCPPT_TEXT("Invalid joypad button id ")
						+
						fcppt::output_to_fcppt_string(
							_id
						)
					};
			}
		).get().first;
}
