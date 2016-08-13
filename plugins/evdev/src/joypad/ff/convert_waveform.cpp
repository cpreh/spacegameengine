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


#include <sge/evdev/joypad/ff/convert_waveform.hpp>
#include <sge/input/joypad/ff/waveform.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


std::uint16_t
sge::evdev::joypad::ff::convert_waveform(
	sge::input::joypad::ff::waveform const _waveform
)
{
	switch(
		_waveform
	)
	{
	case sge::input::joypad::ff::waveform::square:
		return
			FF_SQUARE;
	case sge::input::joypad::ff::waveform::triangle:
		return
			FF_TRIANGLE;
	case sge::input::joypad::ff::waveform::sine:
		return
			FF_SINE;
	case sge::input::joypad::ff::waveform::saw_up:
		return
			FF_SAW_UP;
	case sge::input::joypad::ff::waveform::saw_down:
		return
			FF_SAW_DOWN;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
