//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <sge/camera/matrix_conversion/rotation.hpp>
#include <sge/camera/matrix_conversion/translation.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>

sge::renderer::matrix4 sge::camera::matrix_conversion::world(
    sge::camera::coordinate_system::object const &_coordinate_system)
{
  return sge::camera::matrix_conversion::rotation(_coordinate_system) *
         sge::camera::matrix_conversion::translation(_coordinate_system);
}
