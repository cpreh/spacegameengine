#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/coordinate_system/object.hpp>

sge::camera::coordinate_system::object const
sge::camera::coordinate_system::identity()
{
	return
		sge::camera::coordinate_system::object(
			sge::camera::coordinate_system::right(
				sge::renderer::vector3(
					1.0f,
					0.0f,
					0.0f)),
			sge::camera::coordinate_system::up(
				sge::renderer::vector3(
					0.0f,
					1.0f,
					0.0f)),
			sge::camera::coordinate_system::forward(
				sge::renderer::vector3(
					0.0f,
					0.0f,
					1.0f)),
			sge::camera::coordinate_system::position(
				sge::renderer::vector3(
					0.0f,
					0.0f,
					0.0f)));
}
