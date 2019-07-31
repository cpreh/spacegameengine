//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_CONVERT_RAMP_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_CONVERT_RAMP_HPP_INCLUDED

#include <sge/input/joypad/ff/ramp_fwd.hpp>
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

ff_ramp_effect
convert_ramp(
	sge::input::joypad::ff::ramp const &
);

}
}
}
}

#endif
