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
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/point_sprite_context.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite_texture.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/join_move.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::misc::point_sprite(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::state::ffp::misc::enable_point_sprites const _enable
)
{
	sge::opengl::point_sprite_context &point_sprite_context(
		sge::opengl::context::use<
			sge::opengl::point_sprite_context
		>(
			_system_context
		)
	);

	if(
		!point_sprite_context.is_supported()
	)
	{
		if(
			!_enable.get()
		)
			return
				sge::opengl::state::actor_vector();

		throw sge::renderer::unsupported(
			FCPPT_TEXT("GL_POINT_SPRITE"),
			FCPPT_TEXT("opengl-2.0"),
			FCPPT_TEXT("ARB_point_sprite")
		);
	}

	sge::opengl::texture::multi_context const &multi_context(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			_system_context
		)
	);

	return
		fcppt::algorithm::join_move(
			sge::opengl::state::actor_vector{
				std::bind(
					sge::opengl::enable_bool,
					FCPPT_ASSERT_OPTIONAL_ERROR(
						point_sprite_context.point_sprite_flag()
					),
					_enable.get()
				),
				std::bind(
					sge::opengl::enable_bool,
					FCPPT_ASSERT_OPTIONAL_ERROR(
						point_sprite_context.vertex_shader_size_flag()
					),
					_enable.get()
				)
			},
			fcppt::algorithm::map<
				sge::opengl::state::actor_vector
			>(
				fcppt::make_int_range_count(
					sge::renderer::texture::stage(
						multi_context.max_level().get()
					)
				),
				[
					_enable,
					&_system_context,
					&point_sprite_context
				](
					sge::renderer::texture::stage const _stage
				)
				{
					return
						sge::opengl::state::actor{
							std::bind(
								sge::opengl::state::ffp::misc::point_sprite_texture,
								std::ref(
									_system_context
								),
								std::cref(
									point_sprite_context
								),
								_stage,
								_enable
							)
						};
				}
			)
		);
}
