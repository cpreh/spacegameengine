//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/coordinate_system/forward.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/coordinate_system/position.hpp>
#include <sge/camera/coordinate_system/right.hpp>
#include <sge/camera/coordinate_system/up.hpp>
#include <sge/renderer/vector3.hpp>

sge::camera::coordinate_system::object sge::camera::coordinate_system::identity()
{
  return sge::camera::coordinate_system::object(
      sge::camera::coordinate_system::right(sge::renderer::vector3(1.0F, 0.0F, 0.0F)),
      sge::camera::coordinate_system::up(sge::renderer::vector3(0.0F, 1.0F, 0.0F)),
      sge::camera::coordinate_system::forward(sge::renderer::vector3(0.0F, 0.0F, 1.0F)),
      sge::camera::coordinate_system::position(sge::renderer::vector3(0.0F, 0.0F, 0.0F)));
}
