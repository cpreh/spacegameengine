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


#include <sge/opengl/common.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::texture::volume_context::volume_context()
:
	sge::opengl::context::system::base(),
	volume_texture_normal_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_1_3
		)
	),
	volume_texture_type_(
		volume_texture_normal_
		?
			sge::opengl::texture::optional_type(
				sge::opengl::texture::convert::make_type(
					GL_TEXTURE_3D
				)
			)
		:
			sge::opengl::texture::optional_type()
	),
	tex_image_3d_(
		glTexImage3D
	),
	tex_sub_image_3d_(
		glTexSubImage3D
	),
	max_extent_flag_(
		sge::opengl::optional_enum(
			static_cast<
				GLenum
			>(
				GL_MAX_3D_TEXTURE_SIZE
			)
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::texture::volume_context::~volume_context()
{
}

bool
sge::opengl::texture::volume_context::have_volume_texture() const
{
	return volume_texture_normal_;
}

sge::opengl::texture::optional_type const
sge::opengl::texture::volume_context::volume_texture_type() const
{
	return volume_texture_type_;
}

sge::opengl::texture::volume_context::gl_tex_image_3d
sge::opengl::texture::volume_context::tex_image_3d() const
{
	return tex_image_3d_;
}

sge::opengl::texture::volume_context::gl_tex_sub_image_3d
sge::opengl::texture::volume_context::tex_sub_image_3d() const
{
	return tex_sub_image_3d_;
}

sge::opengl::optional_enum const
sge::opengl::texture::volume_context::max_extent_flag() const
{
	return max_extent_flag_;
}

sge::opengl::context::system::id const
sge::opengl::texture::volume_context::static_id(
	sge::opengl::context::system::make_id()
);
