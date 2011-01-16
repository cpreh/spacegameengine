#include <sge/camera/identity_gizmo.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sge::camera::gizmo_type const
sge::camera::identity_gizmo()
{
	return 
		gizmo_type()
			.position(
				sge::renderer::vector3::null())
			.right(
				sge::renderer::vector3(1,0,0))
			.up(
				sge::renderer::vector3(0,1,0))
			.forward(
				sge::renderer::vector3(0,0,1));
}
