//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/base.hpp>
#include <sge/input/joypad/event/discover.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::joypad::event::discover::discover(sge::input::joypad::shared_ptr _joypad)
    : sge::input::joypad::event::base{std::move(_joypad)}
{
}

sge::input::joypad::event::discover::~discover() = default;
