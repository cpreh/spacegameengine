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
#include "../texture_functions.hpp"
#include "../error.hpp"
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

void sge::ogl::set_texture(const GLenum tex_type,
                           const filter_args& filter,
                           const sge::texture_base::size_type width,
                           const sge::texture_base::size_type height,
                           const sge::texture_base::const_pointer src)
{
	SGE_OPENGL_SENTRY
	
	if(width < 64 || height < 64)
		std::cerr << "warning: opengl implementations are not required to support textures smaller than 64x64."\
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
	
	if(r.right > width || r.bottom > height)
		throw exception("rect for setting a texture is out of range!");

	if(need_mipmap(filter.min_filter))
		throw exception("You can't specify an update rect while using mipmaps. Ignored.");

	glTexSubImage2D(tex_type, 0, static_cast<GLint>(r.left), static_cast<GLint>(r.top), static_cast<GLsizei>(r.w()), static_cast<GLsizei>(r.h()), format, type, src);
}

void sge::ogl::read_pixels(const sge::texture_base::size_type x,
                           const sge::texture_base::size_type y,
                           const sge::texture_base::size_type width,
                           const sge::texture_base::size_type height,
                           const sge::texture_base::pointer dest)
{
	SGE_OPENGL_SENTRY
	
	glReadPixels(x, y, width, height, format, type, dest);
}
