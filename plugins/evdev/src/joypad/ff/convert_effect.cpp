//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/convert_effect.hpp>
#include <sge/evdev/joypad/ff/convert_effect_type.hpp>
#include <sge/evdev/joypad/ff/convert_replay.hpp>
#include <sge/evdev/joypad/ff/convert_trigger.hpp>
#include <sge/evdev/joypad/ff/convert_variant.hpp>
#include <sge/input/joypad/ff/parameters.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

ff_effect sge::evdev::joypad::ff::convert_effect(
    sge::evdev::joypad::button::event_map const &_buttons,
    sge::input::joypad::ff::parameters const &_parameters)
{
  return ff_effect{
      .type = sge::evdev::joypad::ff::convert_effect_type(_parameters.variant()),
      .id = fcppt::literal<std::int16_t>(-1),
      .direction = fcppt::cast::size<std::uint16_t>(
          _parameters.direction().get().get() /
          1000U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      .trigger = sge::evdev::joypad::ff::convert_trigger(_buttons, _parameters.trigger()),
      .replay = sge::evdev::joypad::ff::convert_replay(_parameters.duration(), _parameters.delay()),
      .u = sge::evdev::joypad::ff::convert_variant(_parameters.variant())};
}
