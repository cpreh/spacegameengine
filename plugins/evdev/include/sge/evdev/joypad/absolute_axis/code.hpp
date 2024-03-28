//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_ABSOLUTE_AXIS_CODE_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_ABSOLUTE_AXIS_CODE_HPP_INCLUDED

#include <sge/evdev/joypad/absolute_axis/code_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::joypad::absolute_axis
{

enum class code : std::uint8_t
{
  fcppt_maximum = ABS_MAX
};

}

#endif
