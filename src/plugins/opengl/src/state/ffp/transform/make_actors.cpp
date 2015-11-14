/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/ffp/transform/actor.hpp>
#include <sge/opengl/state/ffp/transform/actor_vector.hpp>
#include <sge/opengl/state/ffp/transform/context.hpp>
#include <sge/opengl/state/ffp/transform/make_actors.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix_and_mode.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::ffp::transform::actor_vector
sge::opengl::state::ffp::transform::make_actors(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::transform::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::transform::actor_vector{
			sge::opengl::state::ffp::transform::actor{
				std::bind(
					&sge::opengl::state::ffp::transform::set_matrix_and_mode,
					std::ref(
						_context
					),
					std::placeholders::_1,
					sge::opengl::context::use<
						sge::opengl::state::ffp::transform::context
					>(
						_context,
						_context.info()
					).have_transpose()
					?
						_parameters.matrix()
					:
						fcppt::math::matrix::transpose(
							_parameters.matrix()
						)
				)
			}
		};
}
