//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_SPHERICAL_ACTION_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_ACTION_MAPPING_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/spherical/action/decrease_azimuth.hpp>
#include <sge/camera/spherical/action/decrease_inclination.hpp>
#include <sge/camera/spherical/action/decrease_radius.hpp>
#include <sge/camera/spherical/action/increase_azimuth.hpp>
#include <sge/camera/spherical/action/increase_inclination.hpp>
#include <sge/camera/spherical/action/increase_radius.hpp>
#include <sge/camera/spherical/action/mapping_fwd.hpp> // IWYU pragma: keep

namespace sge::camera::spherical::action
{

/**
\brief A mapping from camera "actions" to key codes
\ingroup sgecamera
*/
class mapping
{
public:
  SGE_CAMERA_DETAIL_SYMBOL
  mapping(
      sge::camera::spherical::action::increase_azimuth const &,
      sge::camera::spherical::action::decrease_azimuth const &,
      sge::camera::spherical::action::increase_inclination const &,
      sge::camera::spherical::action::decrease_inclination const &,
      sge::camera::spherical::action::increase_radius const &,
      sge::camera::spherical::action::decrease_radius const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::spherical::action::increase_azimuth const &
  increase_azimuth() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::spherical::action::decrease_azimuth const &
  decrease_azimuth() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL
      sge::camera::spherical::action::increase_inclination const &
      increase_inclination() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL
      sge::camera::spherical::action::decrease_inclination const &
      decrease_inclination() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::spherical::action::increase_radius const &
  increase_radius() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::spherical::action::decrease_radius const &
  decrease_radius() const;

private:
  sge::camera::spherical::action::increase_azimuth increase_azimuth_;
  sge::camera::spherical::action::decrease_azimuth decrease_azimuth_;
  sge::camera::spherical::action::increase_inclination increase_inclination_;
  sge::camera::spherical::action::decrease_inclination decrease_inclination_;
  sge::camera::spherical::action::increase_radius increase_radius_;
  sge::camera::spherical::action::decrease_radius decrease_radius_;
};

}

#endif
