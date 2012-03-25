#include <sge/camera/matrix_conversion/rotation.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <fcppt/math/matrix/object_impl.hpp>

sge::renderer::matrix4 const
sge::camera::matrix_conversion::rotation(
	camera::coordinate_system::object const &_coordinate_system)
{
	sge::renderer::vector3 const
		r(
			_coordinate_system.right().get()),
		u(
			_coordinate_system.up().get()),
		f(
			_coordinate_system.forward().get());

	return
		sge::renderer::matrix4(
			r[0],r[1],r[2],0.0f,
			u[0],u[1],u[2],0.0f,
			f[0],f[1],f[2],0.0f,
			0.0f,0.0f,0.0f,1.0f);
}
