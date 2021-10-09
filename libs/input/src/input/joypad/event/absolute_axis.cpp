//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/absolute_axis.hpp>
#include <sge/input/joypad/event/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::joypad::event::absolute_axis::absolute_axis(
    sge::input::joypad::shared_ptr _joypad,
    sge::input::joypad::absolute_axis const &_axis,
    sge::input::joypad::axis_value const _axis_value)
    : sge::input::joypad::event::base{std::move(_joypad)}, axis_{_axis}, axis_value_{_axis_value}
{
}

sge::input::joypad::event::absolute_axis::~absolute_axis() = default;

sge::input::joypad::absolute_axis const &sge::input::joypad::event::absolute_axis::axis() const
{
  return axis_;
}

sge::input::joypad::axis_value sge::input::joypad::event::absolute_axis::value() const
{
  return axis_value_;
}
