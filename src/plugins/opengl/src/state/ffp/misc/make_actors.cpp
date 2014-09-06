/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/common.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/misc/make_actors.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite.hpp>
#include <sge/renderer/state/ffp/misc/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::misc::make_actors(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::state::ffp::misc::parameters const &_parameters
)
{
	return
		fcppt::algorithm::join(
			sge::opengl::state::actor_vector{
				std::bind(
					sge::opengl::enable_bool,
					GL_NORMALIZE,
					_parameters.normalize_normals().get()
				),
				sge::opengl::state::wrap_error_handler<
					sge::opengl::state::actor
				>(
					std::bind(
						::glLightModeli,
						GL_LIGHT_MODEL_LOCAL_VIEWER,
						_parameters.local_viewer().get()
						?
							1
						:
							0
					),
					FCPPT_TEXT("glLightModeli failed")
				)
			},
			sge::opengl::state::ffp::misc::point_sprite(
				_system_context,
				_parameters.enable_point_sprites()
			)
		);
}
