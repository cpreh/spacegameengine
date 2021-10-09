//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/spherical/coordinate_system/object.hpp>

sge::camera::spherical::coordinate_system::object::object(
    spherical::coordinate_system::azimuth const &_azimuth,
    spherical::coordinate_system::inclination const &_inclination,
    spherical::coordinate_system::radius const &_radius)
    : azimuth_(_azimuth), inclination_(_inclination), radius_(_radius)
{
}

sge::camera::spherical::coordinate_system::azimuth const &
sge::camera::spherical::coordinate_system::object::azimuth() const
{
  return azimuth_;
}

void sge::camera::spherical::coordinate_system::object::azimuth(
    spherical::coordinate_system::azimuth const &_azimuth)
{
  azimuth_ = _azimuth;
}

sge::camera::spherical::coordinate_system::inclination const &
sge::camera::spherical::coordinate_system::object::inclination() const
{
  return inclination_;
}

void sge::camera::spherical::coordinate_system::object::inclination(
    spherical::coordinate_system::inclination const &_inclination)
{
  inclination_ = _inclination;
}

sge::camera::spherical::coordinate_system::radius const &
sge::camera::spherical::coordinate_system::object::radius() const
{
  return radius_;
}

void sge::camera::spherical::coordinate_system::object::radius(
    spherical::coordinate_system::radius const &_radius)
{
  radius_ = _radius;
}
