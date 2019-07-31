//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/magnitude.hpp>
#include <sge/input/joypad/ff/offset.hpp>
#include <sge/input/joypad/ff/period.hpp>
#include <sge/input/joypad/ff/periodic.hpp>
#include <sge/input/joypad/ff/phase.hpp>
#include <sge/input/joypad/ff/waveform.hpp>


sge::input::joypad::ff::periodic::periodic(
	sge::input::joypad::ff::waveform const _waveform,
	sge::input::joypad::ff::magnitude const _magnitude,
	sge::input::joypad::ff::offset const _offset,
	sge::input::joypad::ff::phase const _phase,
	sge::input::joypad::ff::period const _period,
	sge::input::joypad::ff::envelope const &_envelope
)
:
	waveform_{
		_waveform
	},
	magnitude_{
		_magnitude
	},
	offset_{
		_offset
	},
	phase_{
		_phase
	},
	period_{
		_period
	},
	envelope_{
		_envelope
	}
{
}

sge::input::joypad::ff::waveform
sge::input::joypad::ff::periodic::waveform() const
{
	return
		waveform_;
}

sge::input::joypad::ff::magnitude
sge::input::joypad::ff::periodic::magnitude() const
{
	return
		magnitude_;
}

sge::input::joypad::ff::offset
sge::input::joypad::ff::periodic::offset() const
{
	return
		offset_;
}

sge::input::joypad::ff::phase
sge::input::joypad::ff::periodic::phase() const
{
	return
		phase_;
}

sge::input::joypad::ff::period
sge::input::joypad::ff::periodic::period() const
{
	return
		period_;
}

sge::input::joypad::ff::envelope const &
sge::input::joypad::ff::periodic::envelope() const
{
	return
		envelope_;
}
