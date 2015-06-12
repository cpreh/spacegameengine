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


#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set_texture.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <sge/opengl/texture/funcs/env_target.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>


void
sge::opengl::state::ffp::misc::point_sprite::set_texture(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::state::ffp::misc::point_sprite::config const &_point_sprite_config,
	sge::renderer::texture::stage const _stage,
	sge::renderer::state::ffp::misc::enable_point_sprites const _enable
)
{
	sge::opengl::texture::active_level const active_level(
		_system_context,
		_stage
	);

	sge::opengl::texture::funcs::env_int(
		active_level,
		sge::opengl::texture::funcs::env_target{
			_point_sprite_config.point_sprite_flag().get()
		},
		sge::opengl::texture::funcs::env_arg{
			_point_sprite_config.coord_replace_flag().get()
		},
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_int_value,
			fcppt::cast::static_cast_fun
		>(
			sge::opengl::convert::to_gl_bool(
				_enable.get()
			)
		)
	);
}
