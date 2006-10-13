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


#ifndef SGE_OGL_TEXTURE_HPP_INCLUDED
#define SGE_OGL_TEXTURE_HPP_INCLUDED

#include "../../renderer/texture.hpp"
#include "./basic_texture.hpp"
#include "./error.hpp"

namespace sge
{
namespace ogl
{

class texture : public basic_texture<sge::texture,GL_TEXTURE_2D> {
public:
	texture(const const_pointer src, const size_type nwidth, const size_type nheight, const unsigned mipmaps, const resource_flag_t flags)
		: basic_texture<sge::texture,GL_TEXTURE_2D>(nwidth*nheight,mipmaps,flags), _width(nwidth), _height(nheight)
	{
		set_data(src);
	}
	size_type width() const { return _width; }
	size_type height() const { return _height; }
	size_type size() const { return width()*height(); }
	void set_data(const const_pointer src, const lock_rect* const r = 0)
	{
		bind_me();
		const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;
		if(!r)
			glTexImage2D(GL_TEXTURE_2D,0,4,width(),height(),0,format,type,src);
		else
			glTexSubImage2D(GL_TEXTURE_2D,0,r->left,r->top,r->width(),r->height(),format,type,src);
		if(is_error())
			throw std::runtime_error("glTex(Sub)Image2D() failed!");
	}
private:
	const size_type _width, _height;
};

}
}

#endif

