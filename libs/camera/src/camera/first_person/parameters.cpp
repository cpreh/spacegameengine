//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/first_person/mouse_speed_multiplier.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/first_person/action/mapping.hpp>
#include <sge/camera/first_person/action/wasd_mapping.hpp>

sge::camera::first_person::parameters::parameters(
    sge::camera::first_person::movement_speed const &_movement_speed,
    sge::camera::coordinate_system::object const _coordinate_system)
    : action_mapping_{sge::camera::first_person::action::wasd_mapping()},
      movement_speed_{_movement_speed},
      coordinate_system_{_coordinate_system},
      mouse_speed_multiplier_{
          0.0025F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      },
      projection_matrix_{}
{
}

sge::camera::first_person::parameters &sge::camera::first_person::parameters::action_mapping(
    sge::camera::first_person::action::mapping const &_action_mapping)
{
  action_mapping_ = _action_mapping;

  return *this;
}

sge::camera::first_person::action::mapping const &
sge::camera::first_person::parameters::action_mapping() const
{
  return action_mapping_;
}

sge::camera::first_person::movement_speed const &
sge::camera::first_person::parameters::movement_speed() const
{
  return movement_speed_;
}

sge::camera::coordinate_system::object const &
sge::camera::first_person::parameters::coordinate_system() const
{
  return coordinate_system_;
}

sge::camera::first_person::parameters &
sge::camera::first_person::parameters::mouse_speed_multiplier(
    sge::camera::first_person::mouse_speed_multiplier const &_mouse_speed_multiplier)
{
  mouse_speed_multiplier_ = _mouse_speed_multiplier;

  return *this;
}

sge::camera::first_person::mouse_speed_multiplier const &
sge::camera::first_person::parameters::mouse_speed_multiplier() const
{
  return mouse_speed_multiplier_;
}

sge::camera::first_person::parameters &sge::camera::first_person::parameters::projection(
    sge::camera::projection_matrix const &_projection_matrix)
{
  projection_matrix_ = sge::camera::optional_projection_matrix(_projection_matrix);

  return *this;
}

sge::camera::optional_projection_matrix const &
sge::camera::first_person::parameters::projection_matrix() const
{
  return projection_matrix_;
}
