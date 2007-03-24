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


#include "../cube_texture.hpp"
#include "../conversion.hpp"
#include "../error.hpp"

sge::ogl::cube_texture::cube_texture(const cube_side_array* const src, const size_type sz, const filter_args& filter, const resource_flag_t flags)
 : basic_texture<sge::cube_texture,GL_TEXTURE_CUBE_MAP_ARB>(filter,flags),
  sz(sz)
{
	if(src)
		set_cube_texture_data(*this,*src);
}


sge::ogl::cube_texture::size_type sge::ogl::cube_texture::size() const
{
	return sz;
}

void sge::ogl::cube_texture::set_data(const cube_side side, const const_pointer src, const lock_rect* const r)
{
	bind_me();
	set_my_filter();
	const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;
	if(!r)
		glTexImage2D(convert_cast<GLenum>(side),0,4,static_cast<GLsizei>(size()),static_cast<GLsizei>(size()),0,format,type,src);
	else
		glTexSubImage2D(convert_cast<GLenum>(side),0,static_cast<GLint>(r->left),static_cast<GLint>(r->top),static_cast<GLsizei>(r->width()),static_cast<GLsizei>(r->height()),format,type,src);
	if(is_error())
		throw std::runtime_error("glTex(Sub)Image2D failed!");
}
