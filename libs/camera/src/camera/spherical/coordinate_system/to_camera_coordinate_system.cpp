//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/coordinate_system/forward.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/coordinate_system/position.hpp>
#include <sge/camera/coordinate_system/right.hpp>
#include <sge/camera/coordinate_system/up.hpp>
#include <sge/camera/spherical/origin.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/camera/spherical/coordinate_system/to_camera_coordinate_system.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/cross.hpp>
#include <fcppt/math/vector/hypersphere_to_cartesian.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace
{

sge::renderer::vector3
spherical_coordinates(sge::camera::spherical::coordinate_system::object const &_coordinate_system)
{
  sge::renderer::vector3 const hypersphere_coords{
      fcppt::math::vector::hypersphere_to_cartesian(sge::renderer::vector2{
          _coordinate_system.inclination().get(), _coordinate_system.azimuth().get()})};

  return sge::renderer::vector3{
      hypersphere_coords.y(), hypersphere_coords.x(), hypersphere_coords.z()};
}
}

fcppt::optional::object<sge::camera::coordinate_system::object>
sge::camera::spherical::coordinate_system::to_camera_coordinate_system(
    sge::camera::spherical::coordinate_system::object const &_coordinate_system,
    sge::camera::spherical::origin const &_origin)
{
  sge::camera::coordinate_system::forward const forward_vector{
      spherical_coordinates(_coordinate_system)};

  sge::camera::coordinate_system::position const position_vector{
      _origin.get() + _coordinate_system.radius().get() * forward_vector.get()};

  return fcppt::optional::map(
      fcppt::math::vector::normalize(fcppt::math::vector::cross(
          forward_vector.get(), sge::renderer::vector3{0.0F, 1.0F, 0.0F})),
      [&forward_vector,&position_vector](sge::renderer::vector3 const _right)
      {
        sge::camera::coordinate_system::right const right_vector{_right};
        // No need to normalize here
        sge::camera::coordinate_system::up const up_vector{
            fcppt::math::vector::cross(right_vector.get(), forward_vector.get())};

        return sge::camera::coordinate_system::object(
            right_vector, up_vector, forward_vector, position_vector);
      });
}
