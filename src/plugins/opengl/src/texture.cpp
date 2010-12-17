/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../basic_texture_impl.hpp"
#include "../lock_flag_read.hpp"
#include "../lock_flag_write.hpp"
#include "../convert_lock_method.hpp"
#include "../texfuncs/set.hpp"
#include "../texfuncs/set_rect.hpp"
#include "../texfuncs/get_image.hpp"
#include "../convert/format_to_color.hpp"
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

template class sge::opengl::basic_texture<sge::renderer::texture>;

namespace
{

GLenum const texture_type = GL_TEXTURE_2D;

}

sge::opengl::texture::texture(
	context::object &_context,
	dim_type const &_dim,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags,
	optional_type const _type
)
:
	detail::texture_base(
		_context,
		_filter,
		_flags,
		_type
		?
			*_type
		:
			texture_type,
		_format
	),
	dim_(_dim)
{
	pre_setdata();

	texfuncs::set(
		_context,
		type(),
		format(),
		format_type(),
		internal_format(),
		filter(),
		dim(),
		0
	);
}

sge::opengl::texture::~texture()
{
}

sge::opengl::texture::dim_type const
sge::opengl::texture::dim() const
{
	return dim_;
}

sge::image2d::view::object const
sge::opengl::texture::lock(
	renderer::lock_rect const &_rect,
	renderer::lock_mode::type const _mode
)
{
	lock_me(
		_rect,
		opengl::convert_lock_method(
			_mode
		)
	);

	return view();
}

sge::image2d::view::const_object const
sge::opengl::texture::lock(
	renderer::lock_rect const &_rect
) const
{
	lock_me(
		_rect,
		lock_method::readonly
	);

	return view();
}

void
sge::opengl::texture::unlock() const
{
	pre_unlock();

	if(
		opengl::lock_flag_write(
			lock_mode()
		)
	)
	{
		bind();

		renderer::lock_rect const lr(
			lock_rect_
			?
				*lock_rect_
			:
				renderer::lock_rect(
					renderer::lock_rect::vector::null(),
					dim()
				)
		);

		texfuncs::set_rect(
			context(),
			type(),
			format(),
			format_type(),
			dim(),
			lr,
			write_buffer()
		);
	}

	do_unlock();
}

void
sge::opengl::texture::lock_me(
	renderer::lock_rect const &_rect,
	lock_method::type const _method
) const
{
	if(
		_rect.right() > dim().w()
		|| _rect.bottom() > dim().h()
	)
		throw renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("ogl: lock_rect (%1%) out of range! dim is %2%!")
				)
				% _rect
				% dim()
			).str()
		);

	bool const must_read(
		opengl::lock_flag_read(
			_method
		)
	);

	bind();

	// if we must read we have to lock the whole texture
	// and set the lock size, the offset and the pitch accordingly
	if(must_read)
		do_lock(
			_method,
			_rect.area(),
			_rect.left() + _rect.top() * dim().w(),
			dim().w() - _rect.dimension().w(),
			_rect.dimension().w()
		);
	else
		do_lock(
			_method,
			_rect.area(),
			0,
			0,
			0
		);

	if(must_read)
		texfuncs::get_image(
			type(),
			format(),
			format_type(),
			read_buffer()
		);

	post_lock();

	if(_rect == rect())
		lock_rect_.reset();
	else
		lock_rect_ = _rect;
}

sge::image2d::view::object const
sge::opengl::texture::view()
{
	return
		image2d::view::make(
			real_write_buffer(),
			lock_dim(),
			convert::format_to_color(
				format(),
				format_type()
			),
			image2d::view::optional_pitch()
		);
}

sge::image2d::view::const_object const
sge::opengl::texture::view() const
{
	return
		image2d::view::make_const(
			static_cast<
				const_pointer
			>(
				real_read_buffer()
			),
			lock_dim(),
			convert::format_to_color(
				format(),
				format_type()
			),
			image2d::view::optional_pitch()
		);
}

sge::opengl::texture::dim_type const
sge::opengl::texture::lock_dim() const
{
	return
		lock_rect_
		?
			lock_rect_->dimension()
		:
			dim();
}
