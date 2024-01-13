//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_INFO_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_INFO_HPP_INCLUDED

#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/info_fwd.hpp> // IWYU pragma: keep
#include <sge/input/joypad/info.hpp>

namespace sge::evdev::joypad
{

class info
{
public:
  info(sge::input::joypad::info &&, sge::evdev::joypad::event_map &&);

  [[nodiscard]] sge::input::joypad::info const &input_info() const;

  [[nodiscard]] sge::evdev::joypad::event_map const &event_map() const;

private:
  sge::input::joypad::info input_info_;

  sge::evdev::joypad::event_map event_map_;
};

}

#endif
