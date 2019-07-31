//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/misc/make_actors.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set.hpp>
#include <sge/renderer/state/ffp/misc/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::misc::make_actors(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::misc::parameters const &_parameters
)
{
	return
		fcppt::container::join(
			sge::opengl::state::actor_vector{
				sge::opengl::state::actor{
					[
						normalize_normals = _parameters.normalize_normals()
					]{
						return
							sge::opengl::enable_bool(
								sge::opengl::convert::to_gl_enum<
									GL_NORMALIZE
								>(),
								normalize_normals.get()
							);
					}
				},
				sge::opengl::state::wrap_error_handler<
					sge::opengl::state::actor
				>(
					[
						local_viewer = _parameters.local_viewer()
					]{
						return
							sge::opengl::call(
								::glLightModeli,
								sge::opengl::convert::to_gl_enum<
									GL_LIGHT_MODEL_LOCAL_VIEWER
								>(),
								local_viewer.get()
								?
									1
								:
									0
							);
					},
					FCPPT_TEXT("glLightModeli failed")
				)
			},
			sge::opengl::state::ffp::misc::point_sprite::set(
				_log,
				_context,
				_parameters.enable_point_sprites()
			)
		);
}
