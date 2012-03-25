#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/matrix_conversion/translation.hpp>
#include <sge/camera/matrix_conversion/rotation.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>

sge::renderer::matrix4 const
sge::camera::matrix_conversion::world(
	camera::coordinate_system::object const &_coordinate_system)
{
	return
		matrix_conversion::rotation(
			_coordinate_system) *
		matrix_conversion::translation(
			_coordinate_system);
}
