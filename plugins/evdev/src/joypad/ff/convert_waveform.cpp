//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
