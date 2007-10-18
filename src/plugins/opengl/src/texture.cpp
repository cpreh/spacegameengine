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


#include "../common.hpp"
#include "../texture.hpp"
#include "../error.hpp"
#include "../texture_functions.hpp"

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

void sge::ogl::texture::set_data(const const_pointer src, const lock_rect& r)
{
	bind_me();
	set_my_filter();
	set_texture_rect(GL_TEXTURE_2D, filter(), width(), height(), r, src);
}

void sge::ogl::texture::set_data(const const_pointer src)
{
	bind_me();
	set_my_filter();
	set_texture_rect(GL_TEXTURE_2D, filter(), width(), height(), src);
}
