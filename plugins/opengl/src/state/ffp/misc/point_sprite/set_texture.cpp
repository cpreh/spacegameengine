//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
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
#include <fcppt/log/object_fwd.hpp>


void
sge::opengl::state::ffp::misc::point_sprite::set_texture(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::opengl::state::ffp::misc::point_sprite::config const &_point_sprite_config,
	sge::renderer::texture::stage const _stage,
	sge::renderer::state::ffp::misc::enable_point_sprites const _enable
)
{
	sge::opengl::texture::active_level const active_level(
		_log,
		_context,
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
