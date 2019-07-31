//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_CONVERT_REPLAY_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_CONVERT_REPLAY_HPP_INCLUDED

#include <sge/input/joypad/ff/delay_fwd.hpp>
#include <sge/input/joypad/ff/optional_duration_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace ff
{

ff_replay
convert_replay(
	sge::input::joypad::ff::optional_duration const &,
	sge::input::joypad::ff::delay
);

}
}
}
}

#endif
