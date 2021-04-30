//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_BUTTON_MAKE_INFO_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_BUTTON_MAKE_INFO_HPP_INCLUDED

#include <sge/evdev/joypad/button/code_fwd.hpp>
#include <sge/input/joypad/button_info_fwd.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace button
{

sge::input::joypad::button_info
make_info(
	sge::evdev::joypad::button::code
);

}
}
}
}

#endif
