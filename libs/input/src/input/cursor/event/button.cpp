//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::event::button::button(
    sge::input::cursor::shared_ptr _cursor,
    sge::input::cursor::button_code const _button_code,
    sge::input::cursor::position const _position,
    sge::input::cursor::button_pressed const _pressed)
    : sge::input::cursor::event::base{std::move(_cursor)},
      button_code_{_button_code},
      position_{_position},
      pressed_{_pressed}
{
}

sge::input::cursor::event::button::~button() = default;

sge::input::cursor::button_code sge::input::cursor::event::button::button_code() const
{
  return button_code_;
}

sge::input::cursor::position sge::input::cursor::event::button::position() const
{
  return position_;
}

bool sge::input::cursor::event::button::pressed() const { return pressed_.get(); }
