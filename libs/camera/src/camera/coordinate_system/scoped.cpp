//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/has_mutable_coordinate_system.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/coordinate_system/scoped.hpp>
#include <fcppt/reference_impl.hpp>

sge::camera::coordinate_system::scoped::scoped(
    fcppt::reference<sge::camera::has_mutable_coordinate_system> const _camera,
    sge::camera::coordinate_system::object const &_coordinate_system)
    : camera_(_camera), old_coordinates_(_camera.get().coordinate_system())
{
  camera_.get().update_coordinate_system(_coordinate_system);
}

sge::camera::coordinate_system::scoped::~scoped()
{
  camera_.get().update_coordinate_system(old_coordinates_);
}
