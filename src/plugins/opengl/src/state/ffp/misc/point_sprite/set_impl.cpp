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


#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set_impl.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set_texture.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::misc::point_sprite::set_impl(
	sge::opengl::context::object &_context,
	sge::opengl::state::ffp::misc::point_sprite::config const &_config,
	sge::renderer::state::ffp::misc::enable_point_sprites const _enable
)
{
	return
		fcppt::algorithm::join(
			sge::opengl::state::actor_vector{
				sge::opengl::state::actor{
					std::bind(
						sge::opengl::enable_bool,
						_config.point_sprite_flag().get(),
						_enable.get()
					)
				},
				sge::opengl::state::actor{
					std::bind(
						sge::opengl::enable_bool,
						_config.vertex_shader_size_flag().get(),
						_enable.get()
					)
				}
			},
			fcppt::algorithm::map<
				sge::opengl::state::actor_vector
			>(
				fcppt::make_int_range_count(
					fcppt::maybe(
						sge::opengl::context::use<
							sge::opengl::texture::multi_context
						>(
							_context,
							_context.info()
						).config(),
						fcppt::const_(
							sge::renderer::texture::stage(
								1u
							)
						),
						[](
							sge::opengl::texture::multi_config const &_multi_config
						)
						{
							return
								sge::renderer::texture::stage(
									_multi_config.max_level().get()
								);
						}
					)
				),
				[
					_enable,
					&_context,
					&_config
				](
					sge::renderer::texture::stage const _stage
				)
				{
					return
						sge::opengl::state::actor{
							std::bind(
								sge::opengl::state::ffp::misc::point_sprite::set_texture,
								std::ref(
									_context
								),
								std::cref(
									_config
								),
								_stage,
								_enable
							)
						};
				}
			)
		);
}
