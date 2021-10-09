//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/axis_code.hpp>

sge::input::joypad::absolute_axis::absolute_axis(
    sge::input::joypad::axis_code const _code, sge::input::joypad::absolute_axis_id const _id)
    : code_(_code), id_(_id)
{
}

sge::input::joypad::axis_code sge::input::joypad::absolute_axis::code() const { return code_; }

sge::input::joypad::absolute_axis_id sge::input::joypad::absolute_axis::id() const { return id_; }
