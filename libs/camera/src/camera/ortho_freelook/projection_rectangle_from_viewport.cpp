//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/camera/ortho_freelook/projection_rectangle_from_viewport.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::ortho_freelook::projection_rectangle_from_viewport::projection_rectangle_from_viewport(
	sge::camera::ortho_freelook::object &_camera,
	sge::viewport::manager &_viewport_manager
)
:
	camera_(
		_camera
	),
	viewport_callback_connection_(
		_viewport_manager.manage_callback(
			sge::viewport::manage_callback{
				std::bind(
					&sge::camera::ortho_freelook::projection_rectangle_from_viewport::viewport_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::camera::ortho_freelook::projection_rectangle_from_viewport::~projection_rectangle_from_viewport()
{
}

void
sge::camera::ortho_freelook::projection_rectangle_from_viewport::viewport_callback(
	sge::renderer::target::viewport const &_viewport
)
{
	camera_.projection_rectangle(
		fcppt::math::box::structure_cast<
			sge::renderer::projection::rect,
			fcppt::cast::int_to_float_fun
		>(
			_viewport.get()
		)
	);
}
