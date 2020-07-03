//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/renderer/projection/aspect.hpp>
#include <sge/renderer/projection/perspective_af.hpp>
#include <sge/renderer/target/aspect_from_viewport.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::perspective_projection_from_viewport::perspective_projection_from_viewport(
	fcppt::reference<
		sge::camera::has_mutable_projection
	> const _camera,
	sge::viewport::manager_ref const _viewport_manager,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far,
	sge::renderer::projection::fov const _fov
)
:
	camera_(
		_camera
	),
	near_(
		_near
	),
	far_(
		_far
	),
	fov_(
		_fov
	),
	viewport_callback_connection_(
		_viewport_manager.get().manage_callback(
			sge::viewport::manage_callback{
				[
					this
				](
					sge::renderer::target::viewport const &_viewport
				)
				{
					this->viewport_callback(
						_viewport
					);
				}
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::camera::perspective_projection_from_viewport::~perspective_projection_from_viewport()
= default;

void
sge::camera::perspective_projection_from_viewport::viewport_callback(
	sge::renderer::target::viewport const &_viewport
)
{
	camera_.get().update_projection_matrix(
		sge::camera::projection_matrix(
			sge::renderer::projection::perspective_af(
				sge::renderer::projection::aspect(
					sge::renderer::target::aspect_from_viewport(
						_viewport
					)
				),
				fov_,
				near_,
				far_
			)
		)
	);
}
