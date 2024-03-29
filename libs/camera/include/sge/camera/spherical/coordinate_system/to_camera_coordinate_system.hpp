//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_TO_CAMERA_COORDINATE_SYSTEM_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_TO_CAMERA_COORDINATE_SYSTEM_HPP_INCLUDED

#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/spherical/origin.hpp>
#include <sge/camera/spherical/coordinate_system/object_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sge::camera::spherical::coordinate_system
{

SGE_CAMERA_DETAIL_SYMBOL
fcppt::optional::object<sge::camera::coordinate_system::object> to_camera_coordinate_system(
    sge::camera::spherical::coordinate_system::object const &,
    sge::camera::spherical::origin const &);
}

#endif
