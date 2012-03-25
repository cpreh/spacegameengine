#include <sge/camera/matrix_conversion/world_projection.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>

sge::renderer::matrix4 const
sge::camera::matrix_conversion::world_projection(
	camera::coordinate_system::object const &_coordinate_system,
	camera::projection_matrix const &_projection)
{
	return
		_projection.get() *
		matrix_conversion::world(
			_coordinate_system);
}
