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


#include <sge/opengl/point_sprite_context.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite_texture.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <sge/opengl/texture/funcs/env_target.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>

void
sge::opengl::state::ffp::misc::point_sprite_texture(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::point_sprite_context const &_point_sprite_context,
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
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_target
		>(
			*_point_sprite_context.point_sprite_flag()
		),
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_arg
		>(
			*_point_sprite_context.coord_replace_flag()
		),
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_int_value
		>(
			sge::opengl::convert::to_gl_bool(
				_enable.get()
			)
		)
	);
}
