//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_FF_CONVERT_DURATION_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_CONVERT_DURATION_HPP_INCLUDED

#include <sge/input/joypad/ff/duration.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::joypad::ff
{

std::uint16_t convert_duration(sge::input::joypad::ff::duration const &);

}

#endif
