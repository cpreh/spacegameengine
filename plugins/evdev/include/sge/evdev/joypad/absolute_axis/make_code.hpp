//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_ABSOLUTE_AXIS_MAKE_CODE_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_ABSOLUTE_AXIS_MAKE_CODE_HPP_INCLUDED

#include <sge/evdev/joypad/absolute_axis/code_fwd.hpp>
#include <sge/input/joypad/axis_code_fwd.hpp>


namespace sge::evdev::joypad::absolute_axis
{

sge::input::joypad::axis_code
make_code(
	sge::evdev::joypad::absolute_axis::code
);

}

#endif
