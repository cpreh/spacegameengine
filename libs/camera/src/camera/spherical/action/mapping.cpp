//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/spherical/action/decrease_azimuth.hpp>
#include <sge/camera/spherical/action/decrease_inclination.hpp>
#include <sge/camera/spherical/action/decrease_radius.hpp>
#include <sge/camera/spherical/action/increase_azimuth.hpp>
#include <sge/camera/spherical/action/increase_inclination.hpp>
#include <sge/camera/spherical/action/increase_radius.hpp>
#include <sge/camera/spherical/action/mapping.hpp>

sge::camera::spherical::action::mapping::mapping(
    sge::camera::spherical::action::increase_azimuth const &_increase_azimuth,
    sge::camera::spherical::action::decrease_azimuth const &_decrease_azimuth,
    sge::camera::spherical::action::increase_inclination const &_increase_inclination,
    sge::camera::spherical::action::decrease_inclination const &_decrease_inclination,
    sge::camera::spherical::action::increase_radius const &_increase_radius,
    sge::camera::spherical::action::decrease_radius const &_decrease_radius)
    : increase_azimuth_(_increase_azimuth),
      decrease_azimuth_(_decrease_azimuth),
      increase_inclination_(_increase_inclination),
      decrease_inclination_(_decrease_inclination),
      increase_radius_(_increase_radius),
      decrease_radius_(_decrease_radius)
{
}

sge::camera::spherical::action::increase_azimuth const &
sge::camera::spherical::action::mapping::increase_azimuth() const
{
  return increase_azimuth_;
}

sge::camera::spherical::action::decrease_azimuth const &
sge::camera::spherical::action::mapping::decrease_azimuth() const
{
  return decrease_azimuth_;
}

sge::camera::spherical::action::increase_inclination const &
sge::camera::spherical::action::mapping::increase_inclination() const
{
  return increase_inclination_;
}

sge::camera::spherical::action::decrease_inclination const &
sge::camera::spherical::action::mapping::decrease_inclination() const
{
  return decrease_inclination_;
}

sge::camera::spherical::action::increase_radius const &
sge::camera::spherical::action::mapping::increase_radius() const
{
  return increase_radius_;
}

sge::camera::spherical::action::decrease_radius const &
sge::camera::spherical::action::mapping::decrease_radius() const
{
  return decrease_radius_;
}
