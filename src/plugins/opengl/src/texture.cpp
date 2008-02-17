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


#include "../../../algorithm_impl.hpp"
#include "../../../renderer/scoped_lock.hpp"
#include "../common.hpp"
#include "../texture.hpp"
#include "../error.hpp"
#include "../texture_functions.hpp"
#include "../basic_texture_impl.hpp"
#include "../vbo.hpp"
#include "../pbo.hpp"

template class sge::ogl::basic_texture<sge::texture, GL_TEXTURE_2D>;

sge::ogl::texture::texture(const const_pointer src,
                           const dim_type& dim_,
                           const filter_args& filter_,
                           const resource_flag_t flags)
 : detail::texture_base(filter_, flags),
   dim_(dim_)
{
	if(src)
		set_data(src);
	else
		set_texture(0);
}

sge::ogl::texture::dim_type sge::ogl::texture::dim() const
{
	return dim_;
}

sge::ogl::texture::size_type sge::ogl::texture::width() const
{
	return dim_.w();
}

sge::ogl::texture::size_type sge::ogl::texture::height() const
{
	return dim_.h();
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
		throw exception(SGE_TEXT("texture::set_data(): src may not be 0!"));
	pre_setdata();

	if(pbo_in_hardware())
	{
		scoped_lock<sge::texture*> lock_(this, lock_flags::writeonly);
		copy_n(src, size(), data());
	}
	else
		set_texture(src);
}

void sge::ogl::texture::lock(const lock_flag_t lmode)
{
	do_lock(lmode);
	if(lock_flag_read(lock_mode()))
		get_tex_image(read_buffer());
	post_lock();
}

void sge::ogl::texture::unlock()
{
	pre_unlock();
	if(lock_flag_write(lock_mode()))
		set_texture(write_buffer());
	do_unlock();
}

void sge::ogl::texture::set_texture(const const_pointer src)
{
	pre_setdata();
	ogl::set_texture(GL_TEXTURE_2D, filter(), width(), height(), src);
}
