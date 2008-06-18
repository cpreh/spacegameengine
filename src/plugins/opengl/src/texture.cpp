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
#include "../pbo.hpp"
#include <sge/algorithm.hpp>
#include <sge/renderer/scoped_lock.hpp>

template class sge::ogl::basic_texture<sge::renderer::texture>;

namespace
{

const GLenum texture_type = GL_TEXTURE_2D;

}

sge::ogl::texture::texture(
	renderer::image const &src,
	const renderer::filter_args& filter_,
	const resource_flag_type flags)
 : detail::texture_base(filter_, flags, texture_type),
   dim_(src.width(), src.height()) // TODO:
{
	set_data(src);
//	else
//		set_texture(0);
}

const sge::ogl::texture::dim_type
sge::ogl::texture::dim() const
{
	return dim_;
}

void sge::ogl::texture::set_data(
	renderer::image const &src,
	renderer::lock_rect const &r)
{
	pre_setdata();
	//set_texture_rect(type(), filter(), dim(), r, src);
}

void sge::ogl::texture::set_data(
	renderer::image const &src)
{
	pre_setdata();

	if(pbo_in_hardware())
	{
		const renderer::scoped_lock<sge::ogl::texture*> lock_(
			renderer::make_scoped_lock(
				this,
				renderer::lock_flags::writeonly));
		//copy_n(src, size(), data());
		// FIXME
	}
//	else
//		set_texture(src);
}

void sge::ogl::texture::lock(
	const lock_flag_type lmode)
{
	do_lock(lmode);
	if(renderer::lock_flag_read(lock_mode()))
		get_tex_image(read_buffer());
	post_lock();
}

void sge::ogl::texture::unlock()
{
	pre_unlock();
	if(renderer::lock_flag_write(lock_mode()))
		set_texture(write_buffer());
	do_unlock();
}

void sge::ogl::texture::set_texture(
	const const_pointer src)
{
	pre_setdata();
	ogl::set_texture(type(), filter(), dim(), src);
}
