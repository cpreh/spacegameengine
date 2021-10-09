//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_RELATIVE_AXIS_MAKE_STRING_HPP_INCLUDED

#include <sge/evdev/joypad/relative_axis/code_fwd.hpp>
#include <fcppt/optional_string.hpp>

namespace sge::evdev::joypad::relative_axis
{

fcppt::optional_string make_string(sge::evdev::joypad::relative_axis::code);

}

#endif
