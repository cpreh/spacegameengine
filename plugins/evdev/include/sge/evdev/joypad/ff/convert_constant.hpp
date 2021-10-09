//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_FF_CONVERT_CONSTANT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_CONVERT_CONSTANT_HPP_INCLUDED

#include <sge/input/joypad/ff/constant_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::joypad::ff
{

ff_constant_effect convert_constant(sge::input::joypad::ff::constant const &);

}

#endif
