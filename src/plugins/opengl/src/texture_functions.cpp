/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../error.hpp"
#include "../conversion.hpp"
#include "../texture_functions.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/iostream.hpp>
#include <sge/format.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/power.hpp>
#include <sge/log/logger.hpp>
#include <sge/log/global.hpp>
#include <ostream>

namespace
{

bool need_mipmap(const sge::renderer::min_filter::type filter)
{
	switch(filter) {
	case sge::renderer::min_filter::mipmap:
	case sge::renderer::min_filter::trilinear:
		return true;
	default:
		return false;
	}
}

}

GLuint sge::ogl::gen_texture()
{
	SGE_OPENGL_SENTRY
	
	GLuint id;
	glGenTextures(1, &id);
	return id;
}

void sge::ogl::delete_texture(const GLuint id)
{
	glDeleteTextures(1, &id);
}

void sge::ogl::set_texture(
	const GLenum tex_type,
	const GLenum format,
	const GLenum type,
	const renderer::filter_args& filter,
	const renderer::texture::dim_type& dim,
	const const_texture_pointer src)
{
	SGE_OPENGL_SENTRY
	
	sge::cerr << SGE_TEXT("texture: ") << dim << SGE_TEXT(", ") << static_cast<void const *>(src) << SGE_TEXT("\n");

	if(dim.w() < 64 || dim.h() < 64)
		log::global(log::level::warning) << SGE_TEXT("warning: opengl implementations are not required to support textures smaller than 64x64.")\
		                                    SGE_TEXT(" Specified texture size was ") << dim << SGE_TEXT(".\n");

	if(!math::is_power_of_2(dim))
		log::global(log::level::warning) << SGE_TEXT("warning: opengl implementations are not required to support textures with dimensions that are not a power of 2.")\
		                                    SGE_TEXT(" Specified texture size was ") << dim << SGE_TEXT(".\n");

	glTexImage2D(
		tex_type,
		0,
		format,
		static_cast<GLsizei>(dim.w()),
		static_cast<GLsizei>(dim.h()),
		0,
		format,
		type,
		src);

	if(need_mipmap(filter.min_filter))
		build_mipmaps(
			tex_type,
			format,
			type,
			dim,
			src);
}

void sge::ogl::build_mipmaps(
	const GLenum tex_type,
	const GLenum format,
	const GLenum type,
	const renderer::texture::dim_type& dim,
	const const_texture_pointer src)
{
	if(!src)
		throw exception(SGE_TEXT("ogl::build_mipmaps: src is 0!"));

	SGE_OPENGL_SENTRY
	
	gluBuild2DMipmaps(
		tex_type,
		format,
		static_cast<GLsizei>(dim.w()),
		static_cast<GLsizei>(dim.h()),
		format,
		type,
		src);
}

void sge::ogl::set_texture_rect(
	const GLenum tex_type,
	const GLenum format,
	const GLenum type,
	const renderer::filter_args& filter,
	const renderer::texture::dim_type& dim,
	const renderer::lock_rect& r,
	const const_texture_pointer src)
{
	SGE_OPENGL_SENTRY
	
	sge::cerr << SGE_TEXT("sub_texture: ") << dim << SGE_TEXT(' ') << r << SGE_TEXT('\n');

	if(!src)
		throw exception(SGE_TEXT("ogl::set_texture_rect(): src is 0!"));

	if(r.right() > dim.w() || r.bottom() > dim.h())
		throw exception(
			(sge::format(
				SGE_TEXT("rect for setting a texture is out of range (rect=%1%, dim=%2%)!"))
				% r
				% dim).str());

	if(need_mipmap(filter.min_filter))
		throw exception(SGE_TEXT("You can't specify an update rect while using mipmaps. Ignored."));

	glTexSubImage2D(
		tex_type,
		0,
		static_cast<GLint>(r.left()),
		static_cast<GLint>(r.top()),
		static_cast<GLsizei>(r.w()),
		static_cast<GLsizei>(r.h()),
		format,
		type,
		src);
}

void sge::ogl::get_tex_image(
	const GLenum format,
	const GLenum type,
	const texture_pointer dest)
{
	SGE_OPENGL_SENTRY
	
	glGetTexImage(
		GL_TEXTURE_2D,
		0,
		format,
		type,
		dest);
}

void sge::ogl::tex_parameter_i(
	const GLenum type,
	const GLenum name,
	const GLint value)
{
	SGE_OPENGL_SENTRY
	
	glTexParameteri(type, name, value);
}

void sge::ogl::bind_texture(
	const GLenum type,
	const GLuint value)
{
	SGE_OPENGL_SENTRY
	
	glBindTexture(type, value);
}

void sge::ogl::set_texture_filter(
	const GLenum type,
	const renderer::filter_args& filter)
{
	tex_parameter_i(type, GL_TEXTURE_MIN_FILTER, convert_cast(filter.min_filter));
	tex_parameter_i(type, GL_TEXTURE_MAG_FILTER, convert_cast(filter.mag_filter));
	if(filter.anisotropy_level)
	{
#if GL_EXT_texture_filter_anisotropic
		try
		{
			tex_parameter_i(type, GL_TEXTURE_MAX_ANISOTROPY_EXT, filter.anisotropy_level);
		}
		catch(const exception&)
		{
			sge::cerr << SGE_TEXT("Warning: anisotropy level ") << filter.anisotropy_level << SGE_TEXT(" not supported!\n");
		}
#else
		sge::cerr << SGE_TEXT("Warning: anisotropic filtering is not supported!\n");
#endif
	}
}
