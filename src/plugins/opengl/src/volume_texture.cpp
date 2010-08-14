/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#if 0
#include "../common.hpp"
#include "../volume_texture.hpp"
#include "../error.hpp"
#include "../version.hpp"
#include "../basic_texture_impl.hpp"
#include <sge/exception.hpp>
#include <fcppt/string.hpp>
#include <sge/once.hpp>
#include <fcppt/math/box_impl.hpp>

namespace
{

void initialize_volume_texture();
GLenum volume_texture_type();

GLenum gl_volume_texture_type;

}

template class sge::opengl::basic_texture<sge::renderer::volume_texture>;

sge::opengl::volume_texture::volume_texture(
	image_view_array const &src,
	renderer::filter_args const &filter,
	resource_flag_type const flags)
: detail::volume_texture_base(
	filter,
	flags,
	volume_texture_type()),
	box_(box_)
{
	//set_data(src);
}

sge::opengl::volume_texture::box_type const
sge::opengl::volume_texture::box() const
{
	return box_;
}

void sge::opengl::volume_texture::data(
	image_view_array const &src)
{
/*	pre_setdata();
	const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;

	SGE_OPENGL_SENTRY

	if(volume_texture_type() == GL_TEXTURE_3D)
		glTexImage3D(
	        	volume_texture_type(),
	        	0,
	        	4,
	        	static_cast<GLsizei>(box().w()),
	        	static_cast<GLsizei>(box().h()),
	        	static_cast<GLsizei>(box().d()),
	        	0,
	        	format,
	        	type,
	        	src);
	else if(volume_texture_type() == GL_TEXTURE_3D_EXT) // avoid possible double case
	{}
		// TODO:*/
}

void sge::opengl::volume_texture::do_sub_data(
	image_view_array const &src,
	renderer::lock_box const &b)
{
/*	if(volume_texture_type() == GL_EXT_texture3D)
		throw exception(
			FCPPT_TEXT("GL_EXT_texture3d can't set sub images!"));

	pre_setdata();
	const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;

	SGE_OPENGL_SENTRY

	glTexSubImage3D(
		volume_texture_type(),
		0,
		static_cast<GLint>(b.left()),
		static_cast<GLint>(b.top()),
		static_cast<GLint>(b.front()),
		static_cast<GLsizei>(b.w()),
		static_cast<GLsizei>(b.h()),
		static_cast<GLsizei>(b.d()),
		format,
		type,
		src);*/
}

void sge::opengl::volume_texture::lock(
	lock_flag_type const flags)
{
}

void sge::opengl::volume_texture::lock(
	renderer::lock_box const &b,
	lock_flag_type const flags)
{
}

void sge::opengl::volume_texture::unlock()
{
}

namespace
{

void initialize_volume_texture()
{
	SGE_FUNCTION_ONCE

	if(GLEW_VERSION_1_2)
		gl_volume_texture_type = GL_TEXTURE_3D;
	else if(GLEW_EXT_texture3D)
		gl_volume_texture_type = GL_TEXTURE_3D_EXT;
	else
		sge::opengl::on_not_supported(
			FCPPT_TEXT("volume_texture"),
			FCPPT_TEXT("1.2"),
			FCPPT_TEXT("gl_ext_texture3d"));
}

GLenum volume_texture_type()
{
	initialize_volume_texture();
	return gl_volume_texture_type;
}

}

#endif
