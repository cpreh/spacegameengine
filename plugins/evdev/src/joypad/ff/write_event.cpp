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


#include <sge/evdev/device/event_value.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/joypad/ff/id.hpp>
#include <sge/evdev/joypad/ff/write_event.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <fcppt/config/external_end.hpp>


void
sge::evdev::joypad::ff::write_event(
	sge::evdev::device::fd const &_fd,
	sge::evdev::joypad::ff::id const _id,
	sge::evdev::device::event_value const _value
)
{
	input_event const event{
		timeval{
			fcppt::literal<
				time_t
			>(
				0
			),
			fcppt::literal<
				suseconds_t
			>(
				0
			)
		},
		EV_FF,
		fcppt::cast::to_unsigned(
			_id.get()
		),
		_value
	};

	if(
		::write(
			_fd.get().get(),
			&event,
			sizeof(
				event
			)
		)
		==
		-1
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Writing a FF event failed")
			};
}
