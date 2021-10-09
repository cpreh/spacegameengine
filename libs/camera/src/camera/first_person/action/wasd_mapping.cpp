//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/first_person/action/mapping.hpp>
#include <sge/camera/first_person/action/wasd_mapping.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/optional_code.hpp>

sge::camera::first_person::action::mapping sge::camera::first_person::action::wasd_mapping()
{
  return sge::camera::first_person::action::mapping(
      sge::camera::first_person::action::left(
          sge::input::key::optional_code(sge::input::key::code::a)),
      sge::camera::first_person::action::right(
          sge::input::key::optional_code(sge::input::key::code::d)),
      sge::camera::first_person::action::up(
          sge::input::key::optional_code(sge::input::key::code::space)),
      sge::camera::first_person::action::down(
          sge::input::key::optional_code(sge::input::key::code::left_control)),
      sge::camera::first_person::action::forward(
          sge::input::key::optional_code(sge::input::key::code::w)),
      sge::camera::first_person::action::backward(
          sge::input::key::optional_code(sge::input::key::code::s)));
}
