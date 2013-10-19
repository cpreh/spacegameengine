/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/state/ffp/sampler/actor_vector.hpp>
#include <sge/opengl/state/ffp/sampler/make_actors.hpp>
#include <sge/opengl/state/ffp/sampler/make_one_op.hpp>
#include <sge/opengl/state/ffp/sampler/set_one.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/algorithm/join.hpp>


sge::opengl::state::ffp::sampler::actor_vector
sge::opengl::state::ffp::sampler::make_actors(
	sge::renderer::state::ffp::sampler::parameters const &_parameters
)
{
	return
		fcppt::algorithm::join(
			sge::opengl::state::ffp::sampler::actor_vector{
				sge::opengl::state::ffp::sampler::set_one(
					fcppt::strong_typedef_construct_cast<
						sge::opengl::texture::funcs::env_arg
					>(
						GL_TEXTURE_ENV_MODE
					),
					fcppt::strong_typedef_construct_cast<
						sge::opengl::texture::funcs::env_int_value
					>(
						GL_COMBINE
					)
				)
			},
			fcppt::algorithm::join(
				sge::opengl::state::ffp::sampler::make_one_op(
					_parameters.color_op()
				),
				sge::opengl::state::ffp::sampler::make_one_op(
					_parameters.alpha_op()
				)
			)
		);
}
