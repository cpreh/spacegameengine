//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_id.hpp>

sge::input::keyboard::key::key(
    sge::input::key::code const _code, sge::input::keyboard::key_id const _id)
    : code_(_code), id_(_id)
{
}

sge::input::key::code sge::input::keyboard::key::code() const { return code_; }

sge::input::keyboard::key_id sge::input::keyboard::key::id() const { return id_; }

bool sge::input::keyboard::operator==(
    sge::input::keyboard::key const &_left, sge::input::keyboard::key const &_right)
{
  return _left.code() == _right.code() && _left.id() == _right.id();
}

bool sge::input::keyboard::operator!=(
    sge::input::keyboard::key const &_left, sge::input::keyboard::key const &_right)
{
  return !(_left == _right);
}
