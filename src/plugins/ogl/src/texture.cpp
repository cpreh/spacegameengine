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

#include "../texture.hpp"
#include "../error.hpp"

sge::ogl::texture::texture(const const_pointer src, const size_type nwidth, const size_type nheight, const unsigned mipmaps, const resource_flag_t flags)
 : basic_texture<sge::texture,GL_TEXTURE_2D>(mipmaps,flags),
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
	const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;
	if(!r)
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width(),height(),0,format,type,src);
	else
		glTexSubImage2D(GL_TEXTURE_2D,0,r->left,r->top,r->width(),r->height(),format,type,src);
	if(is_error())
		throw std::runtime_error("glTex(Sub)Image2D() failed!");
}
