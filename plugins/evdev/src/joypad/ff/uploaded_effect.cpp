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


#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/joypad/ff/id.hpp>
#include <sge/evdev/joypad/ff/uploaded_effect.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::ff::uploaded_effect::uploaded_effect(
	sge::evdev::device::fd const &_fd,
	ff_effect const _effect
)
:
	fd_{
		_fd
	},
	effect_{
		_effect
	}
{
	effect_.id =
		-1;

	if(
		::ioctl(
			fd_.get().get(),
			EVIOCSFF,
			&effect_
		)
		==
		-1
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Uploading a FF effect failed")
			};
}

sge::evdev::joypad::ff::uploaded_effect::~uploaded_effect()
{
	FCPPT_ASSERT_ERROR(
		::ioctl(
			fd_.get().get(),
			EVIOCRMFF,
			&effect_
		)
		!=
		-1
	);
}

sge::evdev::joypad::ff::id
sge::evdev::joypad::ff::uploaded_effect::id() const
{
	return
		sge::evdev::joypad::ff::id{
			effect_.id
		};
}
