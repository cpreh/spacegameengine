//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_HOMOGENOUS_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_HOMOGENOUS_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/renderer/scalar.hpp>

namespace sge::camera::spherical::coordinate_system
{

SGE_CAMERA_DETAIL_SYMBOL
sge::camera::spherical::coordinate_system::object homogenous(sge::renderer::scalar);

}

#endif
