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
#include "../basic_texture_impl.hpp"
#include "../vbo.hpp"
#include "../../../stub.hpp"

template class sge::ogl::basic_texture<sge::texture, GL_TEXTURE_2D>;

sge::ogl::texture::texture(const const_pointer src,
                           const size_type _width,
                           const size_type _height,
                           const filter_args& filter,
                           const resource_flag_t flags)
 : detail::texture_base(filter,flags),
   _width(_width),
   _height(_height)
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

void sge::ogl::texture::lock(const lock_rect& r, const lock_flag_t lflags)
{
	SGE_STUB_FUNCTION
//	lock(r.size(), lflags);
//	glReadBuffer(attachmentpoints[readTex]);
/*	glBindBuffer(GL_PIXEL_PACK_BUFFER_ARB, buf_id);
	glBufferData(GL_PIXEL_PACK_BUFFER_ARB, texSize * texSize * sizeof(float), NULL, GL_STREAM_READ);
	glReadPixels (0, 0, texSize, texSize, GL_LUMINANCE, GL_FLOAT, BUFFER_OFFSET(0));
	void* mem = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY);*/
	//assert(mem);
	//copy(mem,data);
	//glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB);
	//glBindBuffer(GL_PIXEL_PACK_BUFFER_ARB, 0); 
}

void sge::ogl::texture::lock(const lock_flag_t lflags)
{
	do_lock(lflags);
	read_pixels(0, 0, width(), height(), static_cast<color*>(buffer_offset(0)));
}

void sge::ogl::texture::unlock()
{
	do_unlock();
}
