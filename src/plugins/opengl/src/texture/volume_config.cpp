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


#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/volume_config.hpp>


sge::opengl::texture::volume_config::volume_config(
	sge::opengl::texture::type const _volume_texture_type,
	gl_tex_image_3d _tex_image_3d,
	gl_tex_sub_image_3d _tex_sub_image_3d,
	GLenum const _max_extent_flag
)
:
	volume_texture_type_(
		_volume_texture_type
	),
	tex_image_3d_(
		_tex_image_3d
	),
	tex_sub_image_3d_(
		_tex_sub_image_3d
	),
	max_extent_flag_(
		_max_extent_flag
	)
{
}

sge::opengl::texture::type
sge::opengl::texture::volume_config::volume_texture_type() const
{
	return
		volume_texture_type_;
}

sge::opengl::texture::volume_config::gl_tex_image_3d
sge::opengl::texture::volume_config::tex_image_3d() const
{
	return
		tex_image_3d_;
}

sge::opengl::texture::volume_config::gl_tex_sub_image_3d
sge::opengl::texture::volume_config::tex_sub_image_3d() const
{
	return
		tex_sub_image_3d_;
}

GLenum
sge::opengl::texture::volume_config::max_extent_flag() const
{
	return
		max_extent_flag_;
}
