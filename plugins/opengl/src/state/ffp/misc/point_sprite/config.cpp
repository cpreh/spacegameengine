//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/ffp/misc/point_sprite/config.hpp>

sge::opengl::state::ffp::misc::point_sprite::config::config(
    point_sprite_flag_type const _point_sprite_flag,
    vertex_shader_size_flag_type const _vertex_shader_size_flag,
    coord_replace_flag_type const _coord_replace_flag)
    : point_sprite_flag_(_point_sprite_flag),
      vertex_shader_size_flag_(_vertex_shader_size_flag),
      coord_replace_flag_(_coord_replace_flag)
{
}

sge::opengl::state::ffp::misc::point_sprite::config::point_sprite_flag_type
sge::opengl::state::ffp::misc::point_sprite::config::point_sprite_flag() const
{
  return point_sprite_flag_;
}

sge::opengl::state::ffp::misc::point_sprite::config::vertex_shader_size_flag_type
sge::opengl::state::ffp::misc::point_sprite::config::vertex_shader_size_flag() const
{
  return vertex_shader_size_flag_;
}

sge::opengl::state::ffp::misc::point_sprite::config::coord_replace_flag_type
sge::opengl::state::ffp::misc::point_sprite::config::coord_replace_flag() const
{
  return coord_replace_flag_;
}
