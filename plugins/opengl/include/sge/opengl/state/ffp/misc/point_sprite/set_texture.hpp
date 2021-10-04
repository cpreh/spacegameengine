//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_MISC_POINT_SPRITE_SET_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_MISC_POINT_SPRITE_SET_TEXTURE_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config_fwd.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge::opengl::state::ffp::misc::point_sprite
{

void
set_texture(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sge::opengl::context::object &, // NOLINT(google-runtime-references)
	sge::opengl::state::ffp::misc::point_sprite::config const &,
	sge::renderer::texture::stage,
	sge::renderer::state::ffp::misc::enable_point_sprites
);

}

#endif
