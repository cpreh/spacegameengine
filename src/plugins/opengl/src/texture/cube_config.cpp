/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/texture/cube_config.hpp>
#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/texture/type.hpp>


sge::opengl::texture::cube_config::cube_config(
	sge::opengl::texture::type const _cube_texture_type,
	sge::opengl::texture::cube_side_array const &_cube_sides
)
:
	cube_texture_type_(
		_cube_texture_type
	),
	cube_sides_(
		_cube_sides
	)
{
}

sge::opengl::texture::type
sge::opengl::texture::cube_config::cube_texture_type() const
{
	return
		cube_texture_type_;
}

sge::opengl::texture::cube_side_array const &
sge::opengl::texture::cube_config::cube_sides() const
{
	return
		cube_sides_;
}
