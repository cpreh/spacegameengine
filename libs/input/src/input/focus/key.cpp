//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/focus/key.hpp>
#include <sge/input/key/code.hpp>

sge::input::focus::key::key(sge::input::key::code const _code) : code_(_code) {}

sge::input::key::code sge::input::focus::key::code() const { return code_; }

bool sge::input::focus::operator==(
    sge::input::focus::key const &_left, sge::input::focus::key const &_right)
{
  return _left.code() == _right.code();
}

bool sge::input::focus::operator!=(
    sge::input::focus::key const &_left, sge::input::focus::key const &_right)
{
  return !(_left == _right);
}
