//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_BUTTON_CODE_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_BUTTON_CODE_HPP_INCLUDED

#include <sge/evdev/joypad/button/code_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::joypad::button
{

enum class code : std::uint16_t
{
  fcppt_maximum = KEY_MAX
};

}

#endif
