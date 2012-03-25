#include <fcppt/math/matrix/object_impl.hpp>
#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/renderer/projection/perspective_af.hpp>
#include <sge/renderer/projection/aspect.hpp>
#include <sge/renderer/aspect_from_viewport.hpp>
#include <sge/renderer/active_target.hpp>
#include <sge/renderer/target_base.hpp>
#include <fcppt/tr1/functional.hpp>

sge::camera::perspective_projection_from_viewport::perspective_projection_from_viewport(
	sge::camera::has_mutable_projection &_camera,
	sge::renderer::device &_renderer,
	sge::viewport::manager &_viewport_manager,
	sge::renderer::projection::near const &_near,
	sge::renderer::projection::far const &_far,
	sge::renderer::projection::fov const &_fov)
:
	camera_(
		_camera),
	renderer_(
		_renderer),
	near_(
		_near),
	far_(
		_far),
	fov_(
		_fov),
	viewport_callback_connection_(
		_viewport_manager.manage_callback(
			std::tr1::bind(
				&perspective_projection_from_viewport::viewport_callback,
				this)))
{
}

sge::camera::perspective_projection_from_viewport::~perspective_projection_from_viewport()
{
}

void
sge::camera::perspective_projection_from_viewport::viewport_callback()
{
	camera_.projection_matrix(
		sge::camera::projection_matrix(
			sge::renderer::projection::perspective_af(
				sge::renderer::projection::aspect(
					sge::renderer::aspect_from_viewport(
						sge::renderer::active_target(
							renderer_).viewport())),
				fov_,
				near_,
				far_)));
}
