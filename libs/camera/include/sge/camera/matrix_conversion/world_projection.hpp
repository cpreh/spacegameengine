//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_MATRIX_CONVERSION_WORLD_PROJECTION_HPP_INCLUDED
#define SGE_CAMERA_MATRIX_CONVERSION_WORLD_PROJECTION_HPP_INCLUDED

#include <sge/camera/projection_matrix_fwd.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/renderer/matrix4.hpp>


namespace sge::camera::matrix_conversion
{

SGE_CAMERA_DETAIL_SYMBOL
sge::renderer::matrix4
world_projection(
	sge::camera::coordinate_system::object const &,
	sge::camera::projection_matrix const &
);

}

#endif
