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


#include <algorithm>
#include "../../../renderer/scoped_lock.hpp"
#include "../common.hpp"
#include "../texture.hpp"
#include "../error.hpp"
#include "../texture_functions.hpp"
#include "../basic_texture_impl.hpp"
#include "../vbo.hpp"

template class sge::ogl::basic_texture<sge::texture, GL_TEXTURE_2D>;

sge::ogl::texture::texture(const const_pointer src,
                           const size_type _width,
                           const size_type _height,
                           const filter_args& filter_,
                           const resource_flag_t flags)
 : detail::texture_base(filter_, flags),
   _width(_width),
   _height(_height)
{
	if(src)
		set_data(src);
	else
	{
		pre_setdata();
		set_texture_rect(GL_TEXTURE_2D, filter(), width(), height(), 0);
	}
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
	pre_setdata();
	set_texture_rect(GL_TEXTURE_2D, filter(), width(), height(), r, src);
	// TODO: can we use PBO here too?
}

void sge::ogl::texture::set_data(const const_pointer src)
{
	pre_setdata();
	scoped_lock<sge::texture*> lock_(this, lock_flags::writeonly);
	std::copy(src, src + size(), data());
}

void sge::ogl::texture::lock(const lock_flag_t lmode)
{
	do_lock(lmode);
	if(lock_flag_read(lock_mode()))
		read_pixels(0, 0, width(), height(), static_cast<color*>(buffer_offset(0)));
}

void sge::ogl::texture::unlock()
{
	pre_unlock();
	if(lock_flag_write(lock_mode()))
		set_texture_rect(GL_TEXTURE_2D, filter(), width(), height(), static_cast<color*>(buffer_offset(0)));
	do_unlock();
}
