//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/matrix_conversion/world_projection.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>


sge::renderer::matrix4
sge::camera::matrix_conversion::world_projection(
	sge::camera::coordinate_system::object const &_coordinate_system,
	sge::camera::projection_matrix const &_projection
)
{
	return
		_projection.get()
		*
		sge::camera::matrix_conversion::world(
			_coordinate_system
		);
}
