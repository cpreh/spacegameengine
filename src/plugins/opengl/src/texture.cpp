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
#include <sge/renderer/color.hpp>
#include <sge/math/rect_impl.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/gil/extension/dynamic_image/algorithm.hpp>
#include <boost/gil/image_view_factory.hpp>

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
	data_internal(src);
}

sge::ogl::texture::texture(
	dim_type const &d,
	renderer::color_format::type const format_,
	renderer::filter_args const &filter,
	resource_flag_type const flags)
: detail::texture_base(filter, flags, texture_type),
  dim_(d)
{
	format_internal(format_);
	set_texture(0);	
}

const sge::ogl::texture::dim_type
sge::ogl::texture::dim() const
{
	return dim_;
}

void sge::ogl::texture::do_sub_data(
	renderer::const_image_view const &src,
	renderer::lock_rect const &r)
{
	pre_setdata();

	const renderer::scoped_lock<sge::ogl::texture*> lock_(
		renderer::make_scoped_lock(
			this,
			r,
			renderer::lock_flags::writeonly));
	boost::gil::copy_and_convert_pixels(
		src,
		boost::gil::interleaved_view(
			src.width(),
			src.height(),
			reinterpret_cast<renderer::rgba8_pixel*>(write_buffer()),
			src.width() * stride()));
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
	internal_parameters(src);
	
	const renderer::scoped_lock<sge::ogl::texture*> lock_(
		renderer::make_scoped_lock(
			this,
			renderer::lock_flags::writeonly));

	boost::gil::copy_and_convert_pixels(
		src,
		boost::gil::interleaved_view(
			src.width(),
			src.height(),
			reinterpret_cast<renderer::rgba8_pixel*>(write_buffer()),
			src.width() * stride()));
}

void sge::ogl::texture::lock(
	lock_flag_type const lmode)
{
	do_lock(
		lmode,
		size(),
		0);
	if(renderer::lock_flag_read(lock_mode()))
		get_tex_image(
			format(),
			format_type(),
			read_buffer());
	post_lock();
	lock_rect_.reset();
}

void sge::ogl::texture::lock(
	renderer::lock_rect const &l,
	lock_flag_type const lmode)
{
	const bool must_read = renderer::lock_flag_read(lmode);
	do_lock(
		lmode,
		must_read
			? size()
			: l.size(),
		must_read
			? l.left() + l.top() * dim().w()
			: 0);
	if(must_read)
		get_tex_image(
			format(),
			format_type(),
			read_buffer());
	post_lock();
	lock_rect_ = l;
}

void sge::ogl::texture::unlock()
{
	pre_unlock();
	if(renderer::lock_flag_write(lock_mode()))
	{
		if(!lock_rect_)
			set_texture(
				write_buffer());
		else
			set_texture_rect(
				type(),
				format(),
				format_type(),
				filter(),
				dim(),
				*lock_rect_,
				write_buffer());
	}
	do_unlock();
}

sge::renderer::image_view const
sge::ogl::texture::view()
{
	return renderer::image_view(
		boost::gil::rgba8_view_t(
			boost::gil::interleaved_view(
				dim().w(),
				dim().h(),
				reinterpret_cast<renderer::rgba8_pixel*>(
					write_buffer()),
				dim().w() * stride())));
}

sge::renderer::const_image_view const
sge::ogl::texture::view() const
{
	return renderer::const_image_view(
		const_cast<texture&>(*this).view());
}

void sge::ogl::texture::set_texture(
	const_pointer const p)
{
	pre_setdata();
	ogl::set_texture(
		type(),
		format(),
		format_type(),
		filter(),
		dim(),
		p);
}
