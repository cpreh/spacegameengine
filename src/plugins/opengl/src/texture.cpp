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
#include "../../../stub.hpp"
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
		set_texture(0);
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
}

void sge::ogl::texture::set_data(const const_pointer src)
{
	if(!src)
		throw exception("texture::set_data(): src may not be 0!");
	pre_setdata();
#ifdef SGE_OPENGL_HAVE_PBO	
	scoped_lock<sge::texture*> lock_(this, lock_flags::writeonly);
	std::copy(src, src + size(), data());
#else
	set_texture(src);
#endif
}

void sge::ogl::texture::lock(const lock_flag_t lmode)
{
#ifdef SGE_OPENGL_HAVE_PBO
	do_lock(lmode);
	if(lock_flag_read(lock_mode()))
		read_pixels(0,
		            0,
		            width(),
		            height(), static_cast<color*>(buffer_offset(pixel_unpack_buffer_type, 0)));
	post_lock();
#else
	SGE_STUB_FUNCTION
#endif
}

void sge::ogl::texture::unlock()
{
#ifdef SGE_OPENGL_HAVE_PBO
	pre_unlock();
	if(lock_flag_write(lock_mode()))
		set_texture(static_cast<color*>(buffer_offset(pixel_pack_buffer_type, 0)));
	do_unlock();
#else
	SGE_STUB_FUNCTION
#endif
}

void sge::ogl::texture::set_texture(const const_pointer src)
{
	pre_setdata();
	ogl::set_texture(GL_TEXTURE_2D, filter(), width(), height(), src);
}
