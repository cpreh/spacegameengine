/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>
#include <sge/opengl/state/point_sprite.hpp>
//#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <sge/opengl/texture/funcs/env_target.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::state::point_sprite(
	sge::opengl::context::object &_context,
	bool const _enable
)
{
	sge::opengl::point_sprite_context &point_sprite_context(
		sge::opengl::context::use<
			sge::opengl::point_sprite_context
		>(
			_context
		)
	);

	if(
		!point_sprite_context.is_supported()
	)
	{
		if(
			_enable
		)
			return;

		throw sge::renderer::unsupported(
			FCPPT_TEXT("GL_POINT_SPRITE"),
			FCPPT_TEXT("opengl-2.0"),
			FCPPT_TEXT("ARB_point_sprite")
		);
	}

	sge::opengl::enable_bool(
		point_sprite_context.point_sprite_flag(),
		_enable
	);

	sge::opengl::enable_bool(
		point_sprite_context.vertex_shader_size_flag(),
		_enable
	);

#if 0
	sge::opengl::texture::multi_context const &multi_context(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			_context
		)
	);

	for(
		sge::renderer::texture::stage stage(
			0u
		);
		stage.get() < multi_context.max_level().get();
		++stage
	)
#endif
	{
		sge::renderer::texture::stage const stage(
			0u
		);

		sge::opengl::texture::funcs::set_active_level(
			_context,
			stage
		);

		sge::opengl::texture::funcs::env_int(
			fcppt::strong_typedef_construct_cast<
				sge::opengl::texture::funcs::env_target
			>(
				point_sprite_context.point_sprite_flag()
			),
			fcppt::strong_typedef_construct_cast<
				sge::opengl::texture::funcs::env_arg
			>(
				point_sprite_context.coord_replace_flag()
			),
			fcppt::strong_typedef_construct_cast<
				sge::opengl::texture::funcs::env_int_value
			>(
				sge::opengl::convert::to_gl_bool(
					_enable
				)
			)
		);
	}
}
