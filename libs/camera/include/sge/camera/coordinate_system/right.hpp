//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_COORDINATE_SYSTEM_RIGHT_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_RIGHT_HPP_INCLUDED

#include <sge/renderer/vector3.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::camera::coordinate_system
{

/**
\brief The right axis of a coordinate system
\ingroup sgecamera
*/
FCPPT_DECLARE_STRONG_TYPEDEF(sge::renderer::vector3, right);

}

#endif
