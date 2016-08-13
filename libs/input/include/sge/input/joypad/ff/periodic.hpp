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


#ifndef SGE_INPUT_JOYPAD_FF_PERIODIC_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_PERIODIC_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/magnitude.hpp>
#include <sge/input/joypad/ff/offset.hpp>
#include <sge/input/joypad/ff/periodic_fwd.hpp>
#include <sge/input/joypad/ff/period.hpp>
#include <sge/input/joypad/ff/phase.hpp>
#include <sge/input/joypad/ff/waveform.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

class periodic
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	periodic(
		sge::input::joypad::ff::waveform,
		sge::input::joypad::ff::magnitude,
		sge::input::joypad::ff::offset,
		sge::input::joypad::ff::phase,
		sge::input::joypad::ff::period,
		sge::input::joypad::ff::envelope const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::waveform
	waveform() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::magnitude
	magnitude() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::offset
	offset() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::phase
	phase() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::period
	period() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::envelope const &
	envelope() const;
private:
	sge::input::joypad::ff::waveform waveform_;

	sge::input::joypad::ff::magnitude magnitude_;

	sge::input::joypad::ff::offset offset_;

	sge::input::joypad::ff::phase phase_;

	sge::input::joypad::ff::period period_;

	sge::input::joypad::ff::envelope envelope_;
};

}
}
}
}

#endif
