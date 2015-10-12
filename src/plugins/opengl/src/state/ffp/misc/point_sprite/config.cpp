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


#include <sge/opengl/state/ffp/misc/point_sprite/config.hpp>


sge::opengl::state::ffp::misc::point_sprite::config::config(
	point_sprite_flag_type const _point_sprite_flag,
	vertex_shader_size_flag_type const _vertex_shader_size_flag,
	coord_replace_flag_type const _coord_replace_flag
)
:
	point_sprite_flag_(
		_point_sprite_flag
	),
	vertex_shader_size_flag_(
		_vertex_shader_size_flag
	),
	coord_replace_flag_(
		_coord_replace_flag
	)
{
}

sge::opengl::state::ffp::misc::point_sprite::config::point_sprite_flag_type
sge::opengl::state::ffp::misc::point_sprite::config::point_sprite_flag() const
{
	return
		point_sprite_flag_;
}

sge::opengl::state::ffp::misc::point_sprite::config::vertex_shader_size_flag_type
sge::opengl::state::ffp::misc::point_sprite::config::vertex_shader_size_flag() const
{
	return
		vertex_shader_size_flag_;
}

sge::opengl::state::ffp::misc::point_sprite::config::coord_replace_flag_type
sge::opengl::state::ffp::misc::point_sprite::config::coord_replace_flag() const
{
	return
		coord_replace_flag_;
}
