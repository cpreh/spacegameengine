//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/rotation.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/matrix/row.hpp>

sge::renderer::matrix4 sge::camera::matrix_conversion::rotation(
    sge::camera::coordinate_system::object const &_coordinate_system)
{
  sge::renderer::vector3 const r(_coordinate_system.right().get());
  sge::renderer::vector3 const u(_coordinate_system.up().get());
  sge::renderer::vector3 const f(_coordinate_system.forward().get());

  return sge::renderer::matrix4(
      fcppt::math::matrix::row(r.x(), r.y(), r.z(), 0.0F),
      fcppt::math::matrix::row(u.x(), u.y(), u.z(), 0.0F),
      fcppt::math::matrix::row(f.x(), f.y(), f.z(), 0.0F),
      fcppt::math::matrix::row(0.0F, 0.0F, 0.0F, 1.0F));
}
