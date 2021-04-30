//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_CODE_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_CODE_HPP_INCLUDED

#include <sge/evdev/joypad/relative_axis/code_fwd.hpp>
#include <sge/input/joypad/axis_code.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace relative_axis
{

sge::input::joypad::axis_code
make_code(
	sge::evdev::joypad::relative_axis::code
);

}
}
}
}

#endif
