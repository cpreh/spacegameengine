//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_FIRST_PERSON_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_PARAMETERS_HPP_INCLUDED

#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix_fwd.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/first_person/mouse_speed_multiplier.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/action/mapping.hpp>

namespace sge::camera::first_person
{

class parameters
{
public:
  SGE_CAMERA_DETAIL_SYMBOL
  parameters(
      sge::camera::first_person::movement_speed const &, sge::camera::coordinate_system::object);

  SGE_CAMERA_DETAIL_SYMBOL
  parameters &action_mapping(sge::camera::first_person::action::mapping const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::action::mapping const &
  action_mapping() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::movement_speed const &
  movement_speed() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::coordinate_system::object const &
  coordinate_system() const;

  SGE_CAMERA_DETAIL_SYMBOL
  parameters &mouse_speed_multiplier(sge::camera::first_person::mouse_speed_multiplier const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::mouse_speed_multiplier const &
  mouse_speed_multiplier() const;

  // Projection is optional on construction, since we might know it only
  // after we get a viewport.
  SGE_CAMERA_DETAIL_SYMBOL
  parameters &projection(sge::camera::projection_matrix const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::optional_projection_matrix const &
  projection_matrix() const;

private:
  sge::camera::first_person::action::mapping action_mapping_;

  sge::camera::first_person::movement_speed movement_speed_;

  sge::camera::coordinate_system::object coordinate_system_;

  sge::camera::first_person::mouse_speed_multiplier mouse_speed_multiplier_;

  sge::camera::optional_projection_matrix projection_matrix_;
};

}

#endif
