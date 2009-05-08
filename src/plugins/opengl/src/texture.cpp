/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../color_convert.hpp"
#include <sge/renderer/make_image_view.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/format.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

template class sge::ogl::basic_texture<sge::renderer::texture>;

namespace
{

GLenum const texture_type = GL_TEXTURE_2D;

}

sge::ogl::texture::texture(
	dim_type const &d,
	renderer::color_format::type const format_,
	renderer::filter::texture const &filter_,
	resource_flag_type const flags,
	optional_type const type_)
:
	detail::texture_base(
		filter_,
		flags,
		type_ ? *type_ : texture_type,
		format_),
	dim_(d)
{
	pre_setdata();
	set_texture(
		type(),
		format(),
		format_type(),
		filter(),
		dim(),
		0);
}

sge::ogl::texture::dim_type const
sge::ogl::texture::dim() const
{
	return dim_;
}

sge::renderer::image_view const
sge::ogl::texture::lock(
	renderer::lock_rect const &r,
	lock_flag_type const lmode)
{
	lock_me(
		r,
		convert_lock_method(
			lmode));
	return view();
}

sge::renderer::const_image_view const
sge::ogl::texture::lock(
	renderer::lock_rect const &l) const
{
	lock_me(
		l,
		lock_method::readonly);
	return view();
}

void sge::ogl::texture::unlock() const
{
	pre_unlock();
	if(lock_flag_write(lock_mode()))
	{
		bind_me();

		renderer::lock_rect const lr(
			lock_rect_
				? *lock_rect_
				: renderer::lock_rect(
					renderer::lock_rect::point_type::null(),
					dim()));
		set_texture_rect(
			type(),
			format(),
			format_type(),
			filter(),
			dim(),
			lr,
			write_buffer());
	}
	do_unlock();
}

void sge::ogl::texture::lock_me(
	renderer::lock_rect const &l,
	lock_method::type const method) const
{
	if(l.right() > dim().w()
	|| l.bottom() > dim().h())
		throw exception(
			(sge::format(
				SGE_TEXT("ogl: lock_rect (%1%) out of range! dim is %2%!"))
				% l % dim()).str());

	bool const must_read = lock_flag_read(method);

	// if we must read we have to lock the whole texture
	// and set the lock size, the offset and the pitch accordingly
	if(must_read)
		do_lock(
			method,
			l.area(),
			l.left() + l.top() * dim().w(),
			dim().w() - l.dim().w(),
			l.dim().w());
	else
		do_lock(
			method,
			l.area(),
			0,
			0,
			0);
	
	if(must_read)
		get_tex_image(
			format(),
			format_type(),
			read_buffer());

	post_lock();

	if(l == rect())
		lock_rect_.reset();
	else
		lock_rect_ = l;
}

sge::renderer::image_view const
sge::ogl::texture::view()
{
	return renderer::make_image_view(
		real_write_buffer(),
		lock_dim(),
		color_convert(
			format(),
			format_type()));
}

sge::renderer::const_image_view const
sge::ogl::texture::view() const
{
	return renderer::make_image_view(
		static_cast<const_pointer>(
			real_read_buffer()),
		lock_dim(),
		color_convert(
			format(),
			format_type()));
}

sge::ogl::texture::dim_type const
sge::ogl::texture::lock_dim() const
{
	return lock_rect_
		? lock_rect_->dim()
		: dim();
}
