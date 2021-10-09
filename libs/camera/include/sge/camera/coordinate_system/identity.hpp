//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_COORDINATE_SYSTEM_IDENTITY_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_IDENTITY_HPP_INCLUDED

#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>

namespace sge::camera::coordinate_system
{

/**
\brief Returns the canonical coordinate system
\ingroup sgecamera

This sets right to (1,0,0), up to (0,1,0), forward to (0,0,1) and position to
the origin. Classes like sge::camera::first_person::parameters use this
coordinate system as a sensible default.
*/
SGE_CAMERA_DETAIL_SYMBOL
sge::camera::coordinate_system::object identity();

}

#endif
