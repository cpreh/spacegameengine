//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_IS_JOYPAD_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_IS_JOYPAD_HPP_INCLUDED

#include <sge/evdev/joypad/info_fwd.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{

bool
is_joypad(
	sge::evdev::joypad::info const &
);

}
}
}

#endif
