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
#include <sge/renderer/scoped_lock.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

template class sge::ogl::basic_texture<sge::renderer::texture>;

namespace
{

const GLenum texture_type = GL_TEXTURE_2D;

}

sge::ogl::texture::texture(
	renderer::const_image_view const &src,
	const renderer::filter_args& filter_,
	const resource_flag_type flags)
 : detail::texture_base(filter_, flags, texture_type),
   dim_(renderer::gil_dim_to_sge(src.dimensions()))
{
	data(src);
}

const sge::ogl::texture::dim_type
sge::ogl::texture::dim() const
{
	return dim_;
}

void sge::ogl::texture::sub_data(
	renderer::const_image_view const &src,
	renderer::lock_rect const &r)
{
	pre_setdata();
	/*set_texture_rect(
		type(),
		format(),
		format_type(),
		filter(),
		dim(),
		r,
		src);*/
}

void sge::ogl::texture::data(
	renderer::const_image_view const &src)
{
	dim_ = renderer::gil_dim_to_sge(src.dimensions());
	data_internal(src);
}

void sge::ogl::texture::data_internal(
	renderer::const_image_view const &src)
{
	pre_setdata();
	internal_parameters(src);

	if(pbo_in_hardware())
	{
		allocate_texture(src);
			
		const renderer::scoped_lock<sge::ogl::texture*> lock_(
			renderer::make_scoped_lock(
				this,
				renderer::lock_flags::writeonly));
		//boost::gil::copy_pixels(src.begin(), src.end(),
		//boost::gil::raw_view(write_buffer()));
		// FIXME
	}
//	else
//		set_texture(src);
}

void sge::ogl::texture::allocate_texture(
	renderer::const_image_view const &src)
{
	pre_setdata();	
	ogl::set_texture(
		type(),
		0,//convert_format(src),
		0,//convert_type(src),
		filter(),
		dim(),
		0);
}

void sge::ogl::texture::lock(
	const lock_flag_type lmode)
{
	do_lock(
		lmode,
		size());
	if(renderer::lock_flag_read(lock_mode()))
		get_tex_image(
			0,//format(),
			0,//format_type(),
			read_buffer());
	post_lock();
}

void sge::ogl::texture::lock(
	renderer::lock_rect const &l,
	const lock_flag_type lmode)
{
	/*do_lock(
		lmode,
		l.size());
	if(renderer::lock_flag_read(lock_mode()))
		get_tex_image(
			read_buffer(),
			l);
	post_lock();*/
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
	//ogl::set_texture(type(), filter(), dim(), src);
}
