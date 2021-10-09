//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/spherical/coordinate_system/azimuth.hpp>
#include <sge/camera/spherical/coordinate_system/inclination.hpp>
#include <sge/camera/spherical/coordinate_system/look_down_positive_z.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/camera/spherical/coordinate_system/radius.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <numbers>
#include <fcppt/config/external_end.hpp>

sge::camera::spherical::coordinate_system::object
sge::camera::spherical::coordinate_system::look_down_positive_z(
    sge::camera::spherical::coordinate_system::radius const &_radius)
{
  constexpr sge::renderer::scalar const two{2.0F};

  return sge::camera::spherical::coordinate_system::object(
      sge::camera::spherical::coordinate_system::azimuth(
          -std::numbers::pi_v<sge::renderer::scalar> / two),
      sge::camera::spherical::coordinate_system::inclination(
          -std::numbers::pi_v<sge::renderer::scalar> / two),
      _radius);
}
