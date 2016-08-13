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
#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/find_button.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
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
	// TODO: Use a bimap here?
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
						fcppt::insert_to_fcppt_string(
							_id
						)
					};
			}
		).get().first;
}
