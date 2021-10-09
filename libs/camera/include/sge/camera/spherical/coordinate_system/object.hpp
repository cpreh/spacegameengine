//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/spherical/coordinate_system/azimuth.hpp>
#include <sge/camera/spherical/coordinate_system/inclination.hpp>
#include <sge/camera/spherical/coordinate_system/radius.hpp>

namespace sge::camera::spherical::coordinate_system
{

class object
{
public:
  SGE_CAMERA_DETAIL_SYMBOL
  object(
      sge::camera::spherical::coordinate_system::azimuth const &,
      sge::camera::spherical::coordinate_system::inclination const &,
      sge::camera::spherical::coordinate_system::radius const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::spherical::coordinate_system::azimuth const &
  azimuth() const;

  SGE_CAMERA_DETAIL_SYMBOL
  void azimuth(spherical::coordinate_system::azimuth const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL
      sge::camera::spherical::coordinate_system::inclination const &
      inclination() const;

  SGE_CAMERA_DETAIL_SYMBOL
  void inclination(spherical::coordinate_system::inclination const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::spherical::coordinate_system::radius const &
  radius() const;

  SGE_CAMERA_DETAIL_SYMBOL
  void radius(sge::camera::spherical::coordinate_system::radius const &);

private:
  sge::camera::spherical::coordinate_system::azimuth azimuth_;

  sge::camera::spherical::coordinate_system::inclination inclination_;

  sge::camera::spherical::coordinate_system::radius radius_;
};

}

#endif
