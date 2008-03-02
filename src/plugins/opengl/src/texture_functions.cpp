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


#include <iostream>
#include <ostream>
#include "../../../exception.hpp"
#include "../../../math/rect_impl.hpp"
#include "../../../math/utility.hpp"
#include "../error.hpp"
#include "../conversion.hpp"
#include "../texture_functions.hpp"
#include <GL/glu.h>

namespace
{

bool need_mipmap(const sge::min_filter::type filter)
{
	switch(filter) {
	case sge::min_filter::mipmap:
	case sge::min_filter::trilinear:
		return true;
	default:
		return false;
	}
}

const GLenum format = GL_RGBA,
             type = GL_UNSIGNED_BYTE;

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

void sge::ogl::set_texture(const GLenum tex_type,
                           const filter_args& filter,
                           const sge::texture_base::size_type width,
                           const sge::texture_base::size_type height,
                           const sge::texture_base::const_pointer src)
{
	SGE_OPENGL_SENTRY
	
	// TODO: clean this up and use texture::dim_type

	if(width < 64 || height < 64)
		std::cerr << "warning: opengl implementations are not required to support textures smaller than 64x64."\
		             " Specified texture size was " << width << 'x' << height << ".\n";

	if(!math::is_int_log2(width) || !math::is_int_log2(height))
		std::cerr << "warning: opengl implementations are not required to support textures with dimensions that are not a power of 2."\
		             " Specified texture size was " << width << 'x' << height << ".\n";

	glTexImage2D(tex_type, 0, format, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, format, type, src);

	if(need_mipmap(filter.min_filter))
		build_mipmaps(tex_type, width, height, src);
}

void sge::ogl::build_mipmaps(const GLenum tex_type,
                             const sge::texture_base::size_type width,
                             const sge::texture_base::size_type height,
                             const sge::texture_base::const_pointer src)
{
	if(!src)
		throw exception(SGE_TEXT("ogl::build_mipmaps: src is 0!"));

	SGE_OPENGL_SENTRY
	
	gluBuild2DMipmaps(tex_type, format, static_cast<GLsizei>(width), static_cast<GLsizei>(height), format, type, src);
}

void sge::ogl::set_texture_rect(const GLenum tex_type,
                                const filter_args& filter,
                                const sge::texture_base::size_type width,
                                const sge::texture_base::size_type height,
                                const lock_rect& r,
                                const sge::texture_base::const_pointer src)
{
	SGE_OPENGL_SENTRY
	
	if(!src)
		throw exception(SGE_TEXT("ogl::set_texture_rect(): src is 0!"));

	if(r.right() > width || r.bottom() > height)
		throw exception(SGE_TEXT("rect for setting a texture is out of range!"));

	if(need_mipmap(filter.min_filter))
		throw exception(SGE_TEXT("You can't specify an update rect while using mipmaps. Ignored."));

	glTexSubImage2D(tex_type,
	                0,
	                static_cast<GLint>(r.left()),
	                static_cast<GLint>(r.top()),
	                static_cast<GLsizei>(r.w()),
	                static_cast<GLsizei>(r.h()), format, type, src);
}

void sge::ogl::read_pixels(const sge::texture_base::size_type x,
                           const sge::texture_base::size_type y,
                           const sge::texture_base::size_type width,
                           const sge::texture_base::size_type height,
                           const sge::texture_base::pointer dest)
{
	SGE_OPENGL_SENTRY
	
	glReadPixels(static_cast<GLint>(x),
	             static_cast<GLint>(y),
	             static_cast<GLsizei>(width),
	             static_cast<GLsizei>(height),
	             format,
	             type,
	             dest);
}

void sge::ogl::get_tex_image(const sge::texture::pointer dest)
{
	SGE_OPENGL_SENTRY
	
	glGetTexImage(GL_TEXTURE_2D,
	              0,
	              format,
	              type,
	              dest);
}

void sge::ogl::tex_parameter_i(const GLenum type,
                               const GLenum name,
                               const GLint value)
{
	SGE_OPENGL_SENTRY
	
	glTexParameteri(type, name, value);
}

void sge::ogl::bind_texture(const GLenum type,
                            const GLuint value)
{
	SGE_OPENGL_SENTRY
	
	glBindTexture(type, value);
}

void sge::ogl::set_texture_filter(const GLenum type,
                                  const filter_args& filter)
{
	tex_parameter_i(type, GL_TEXTURE_MIN_FILTER, convert_cast<GLenum>(filter.min_filter));
	tex_parameter_i(type, GL_TEXTURE_MAG_FILTER, convert_cast<GLenum>(filter.mag_filter));
	if(filter.anisotropy_level)
	{
#if GL_EXT_texture_filter_anisotropic
		try
		{
			tex_parameter_i(type, GL_TEXTURE_MAX_ANISOTROPY_EXT, filter.anisotropy_level);
		}
		catch(const exception&)
		{
			std::cerr << "Warning: anisotropy level " << filter.anisotropy_level << " not supported!\n";
		}
#else
		std::cerr << "Warning: anisotropic filtering is not supported!\n";
#endif
	}
}
