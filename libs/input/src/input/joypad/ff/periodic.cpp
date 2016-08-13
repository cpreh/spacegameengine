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
