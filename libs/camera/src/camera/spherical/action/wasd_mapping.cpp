//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/spherical/action/decrease_azimuth.hpp>
#include <sge/camera/spherical/action/decrease_inclination.hpp>
#include <sge/camera/spherical/action/decrease_radius.hpp>
#include <sge/camera/spherical/action/mapping.hpp>
#include <sge/camera/spherical/action/increase_azimuth.hpp>
#include <sge/camera/spherical/action/increase_inclination.hpp>
#include <sge/camera/spherical/action/increase_radius.hpp>
#include <sge/camera/spherical/action/wasd_mapping.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/optional_code.hpp>

sge::camera::spherical::action::mapping sge::camera::spherical::action::wasd_mapping()
{
  return sge::camera::spherical::action::mapping(
      sge::camera::spherical::action::increase_azimuth(
          sge::input::key::optional_code(sge::input::key::code::d)),
      sge::camera::spherical::action::decrease_azimuth(
          sge::input::key::optional_code(sge::input::key::code::a)),
      sge::camera::spherical::action::increase_inclination(
          sge::input::key::optional_code(sge::input::key::code::w)),
      sge::camera::spherical::action::decrease_inclination(
          sge::input::key::optional_code(sge::input::key::code::s)),
      sge::camera::spherical::action::increase_radius(
          sge::input::key::optional_code(sge::input::key::code::left_control)),
      sge::camera::spherical::action::decrease_radius(
          sge::input::key::optional_code(sge::input::key::code::space)));
}
