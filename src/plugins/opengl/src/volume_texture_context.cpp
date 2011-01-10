/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../volume_texture_context.hpp"
#include "../common.hpp"
#include "../context/make_id.hpp"
#include "../glew/is_supported.hpp"

sge::opengl::volume_texture_context::volume_texture_context()
:
	volume_texture_normal_(
		sge::opengl::glew::is_supported("GL_VERSION_1_3")
	),
	volume_texture_type_(
		GL_TEXTURE_3D
	),
	tex_image_3d_(
		glTexImage3D
	),
	tex_sub_image_3d_(
		glTexSubImage3D
	)
{
}

sge::opengl::volume_texture_context::~volume_texture_context()
{
}

bool
sge::opengl::volume_texture_context::have_volume_texture() const
{
	return volume_texture_normal_;
}

GLenum
sge::opengl::volume_texture_context::volume_texture_type() const
{
	return volume_texture_type_;	
}

sge::opengl::volume_texture_context::gl_tex_image_3d
sge::opengl::volume_texture_context::tex_image_3d() const
{
	return tex_image_3d_;
}

sge::opengl::volume_texture_context::gl_tex_sub_image_3d
sge::opengl::volume_texture_context::tex_sub_image_3d() const
{
	return tex_sub_image_3d_;
}

sge::opengl::context::id const
sge::opengl::volume_texture_context::static_id(
	sge::opengl::context::make_id()
);
