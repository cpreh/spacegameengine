/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/ffp/sampler/actor_vector.hpp>
#include <sge/opengl/state/ffp/sampler/make_actors.hpp>
#include <sge/opengl/state/ffp/sampler/make_one_op.hpp>
#include <sge/opengl/state/ffp/sampler/set_one.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>
#include <fcppt/container/join.hpp>


sge::opengl::state::ffp::sampler::actor_vector
sge::opengl::state::ffp::sampler::make_actors(
	sge::renderer::state::ffp::sampler::parameters const &_parameters
)
{
	return
		fcppt::container::join(
			sge::opengl::state::ffp::sampler::actor_vector{
				sge::opengl::state::ffp::sampler::set_one(
					sge::opengl::texture::funcs::env_arg{
						sge::opengl::convert::to_gl_enum<
							GL_TEXTURE_ENV_MODE
						>()
					},
					sge::opengl::texture::funcs::env_int_value{
						GL_COMBINE
					}
				)
			},
			sge::opengl::state::ffp::sampler::make_one_op(
				_parameters.color_op()
			),
			sge::opengl::state::ffp::sampler::make_one_op(
				_parameters.alpha_op()
			)
		);
}
