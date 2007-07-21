/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../common.hpp"
#include <GL/glu.h>
#include "../texture.hpp"
#include "../error.hpp"

sge::ogl::texture::texture(const const_pointer src, const size_type nwidth, const size_type nheight, const filter_args& filter, const resource_flag_t flags)
 : basic_texture<sge::texture,GL_TEXTURE_2D>(filter,flags),
   _width(nwidth), _height(nheight)
{
	set_data(src);
}

sge::ogl::texture::size_type sge::ogl::texture::width() const
{
	return _width;
}

sge::ogl::texture::size_type sge::ogl::texture::height() const
{
	return _height;
}

sge::ogl::texture::size_type sge::ogl::texture::size() const
{
	return width()*height();
}

void sge::ogl::texture::set_data(const const_pointer src, const lock_rect* const r)
{
	bind_me();
	set_my_filter();
	const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;
	if(!r)
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,static_cast<GLsizei>(width()),static_cast<GLsizei>(height()),0,format,type,src);
	else
		glTexSubImage2D(GL_TEXTURE_2D,0,static_cast<GLint>(r->left),static_cast<GLint>(r->top),static_cast<GLsizei>(r->width()),static_cast<GLsizei>(r->height()),format,type,src);

	if(this->filter().mip_levels != 1 && !r) // FIXME: don't know what to do if only a portion is updated
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, static_cast<GLsizei>(width()), static_cast<GLsizei>(height()), format, type, src);

	if(is_error())
		throw exception("glTex(Sub)Image2D() failed!");
}
