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


#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>
#include <sge/opengl/texture/context.hpp>


sge::opengl::texture::context::context()
:
	opengl::context::base(),
	anisotropic_filter_supported_(
		sge::opengl::glew::is_supported(
			"GL_EXT_texture_filter_anisotropic"
		)
	),
	generate_mipmap_flag_supported_(
		sge::opengl::glew::is_supported(
			"GL_VERSION_1_4"
		)
	),
	anisotropy_flag_(
		anisotropic_filter_supported_
		?
			GL_TEXTURE_MAX_ANISOTROPY_EXT
		:
			0
	),
	max_anisotropy_flag_(
		anisotropic_filter_supported_
		?
			GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
		:
			0
	)
{
}

sge::opengl::texture::context::~context()
{
}

bool
sge::opengl::texture::context::anisotropic_filter_supported() const
{
	return anisotropic_filter_supported_;
}

bool
sge::opengl::texture::context::generate_mipmap_flag_supported() const
{
	return generate_mipmap_flag_supported_;
}

GLenum
sge::opengl::texture::context::anisotropy_flag() const
{
	return anisotropy_flag_;
}

GLenum
sge::opengl::texture::context::max_anisotropy_flag() const
{
	return max_anisotropy_flag_;
}

sge::opengl::context::id const
sge::opengl::texture::context::static_id(
	sge::opengl::context::make_id()
);
