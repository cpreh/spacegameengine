//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/camera/ortho_freelook/action/wsg_mapping.hpp>
#include <sge/input/key/optional_code.hpp>

sge::camera::ortho_freelook::action::mapping sge::camera::ortho_freelook::action::wsg_mapping()
{
  return sge::camera::ortho_freelook::action::mapping(
      sge::camera::ortho_freelook::action::zoom_in(
          sge::input::key::optional_code(sge::input::key::code::w)),
      sge::camera::ortho_freelook::action::zoom_out(
          sge::input::key::optional_code(sge::input::key::code::s)),
      sge::camera::ortho_freelook::action::activate_pan(
          sge::input::key::optional_code(sge::input::key::code::g)));
}
