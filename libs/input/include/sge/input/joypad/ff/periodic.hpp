//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_PERIODIC_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_PERIODIC_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/magnitude.hpp>
#include <sge/input/joypad/ff/offset.hpp>
#include <sge/input/joypad/ff/period.hpp>
#include <sge/input/joypad/ff/periodic_fwd.hpp>
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
