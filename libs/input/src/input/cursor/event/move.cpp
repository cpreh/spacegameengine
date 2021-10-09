//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::event::move::move(
    sge::input::cursor::shared_ptr _cursor, sge::input::cursor::optional_position const _position)
    : sge::input::cursor::event::base{std::move(_cursor)}, position_{_position}
{
}

sge::input::cursor::event::move::~move() = default;

sge::input::cursor::optional_position const &sge::input::cursor::event::move::position() const
{
  return position_;
}
