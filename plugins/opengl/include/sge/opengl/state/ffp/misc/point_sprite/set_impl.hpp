//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_MISC_POINT_SPRITE_SET_IMPL_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_MISC_POINT_SPRITE_SET_IMPL_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/const_config_ref.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <fcppt/log/object_reference.hpp>

namespace sge::opengl::state::ffp::misc::point_sprite
{

sge::opengl::state::actor_vector set_impl(
    fcppt::log::object_reference,
    sge::opengl::context::object_ref,
    sge::opengl::state::ffp::misc::point_sprite::const_config_ref,
    sge::renderer::state::ffp::misc::enable_point_sprites);

}

#endif
