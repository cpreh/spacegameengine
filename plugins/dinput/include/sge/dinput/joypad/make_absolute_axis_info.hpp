//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_JOYPAD_MAKE_ABSOLUTE_AXIS_INFO_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_MAKE_ABSOLUTE_AXIS_INFO_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/input/joypad/absolute_axis_info_fwd.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{

sge::input::joypad::absolute_axis_info
make_absolute_axis_info(
	IDirectInputDevice8 &,
	DIDEVICEOBJECTINSTANCE const &
);

}
}
}

#endif
