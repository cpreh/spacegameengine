#include <sge/camera/matrix_conversion/translation.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/matrix/translation.hpp>

sge::renderer::matrix4 const
sge::camera::matrix_conversion::translation(
	camera::coordinate_system::object const &_coordinate_system)
{
	return
		fcppt::math::matrix::translation(
			_coordinate_system.position().get());
}
