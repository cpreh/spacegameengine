//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_EVENT_MAP_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_EVENT_MAP_HPP_INCLUDED

#include <sge/evdev/device/event_map.hpp>
#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>

namespace sge::evdev::joypad
{

class event_map
{
public:
  using absolute_axis_map = sge::evdev::device::event_map<sge::input::joypad::absolute_axis_id>;

  using button_map = sge::evdev::joypad::button::event_map;

  using relative_axis_map = sge::evdev::device::event_map<sge::input::joypad::relative_axis_id>;

  event_map(absolute_axis_map &&, button_map &&, relative_axis_map &&);

  [[nodiscard]] absolute_axis_map const &absolute_axis() const;

  [[nodiscard]] button_map const &buttons() const;

  [[nodiscard]] relative_axis_map const &relative_axis() const;

private:
  absolute_axis_map absolute_axis_;

  button_map buttons_;

  relative_axis_map relative_axis_;
};

}

#endif
