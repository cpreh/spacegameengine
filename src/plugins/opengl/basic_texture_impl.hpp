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


#ifndef SGE_OPENGL_BASIC_TEXTURE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TEXTURE_IMPL_HPP_INCLUDED

#include "basic_texture.hpp"
#include "common.hpp"
#include "convert_lock_method.hpp"
#include "create_texture_lock.hpp"
#include "lock_flag_read.hpp"
#include "lock_flag_write.hpp"
#include "range_check.hpp"
#include "convert/color_to_format.hpp"
#include "convert/color_to_format_type.hpp"
#include "convert/color_to_internal_format.hpp"
#include "convert/format_to_color.hpp"
#include "texfuncs/get_image.hpp"
#include "texfuncs/set_filter.hpp"
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/to_const.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/format.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::dim_type const
sge::opengl::basic_texture<Base>::dim() const
{
	return dim_;
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::view_type const
sge::opengl::basic_texture<Base>::lock(
	lock_area const &_area,
	renderer::lock_mode::type const _mode
)
{
	lock_me(
		_area,
		opengl::convert_lock_method(
			_mode
		)
	);

	return view();
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::const_view_type const
sge::opengl::basic_texture<Base>::lock(
	lock_area const &_area
) const
{
	lock_me(
		_area,
		lock_method::readonly
	);

	return view();
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::unlock() const
{
	check_locked();

	lock_->pre_unlock();

	if(
		opengl::lock_flag_write(
			lock_->method()
		)
	)
	{
		bind();

		// if this is also a read lock
		// we must copy the current view, which is
		// a slice into the whole texture retrieved,
		// to the destination buffer
		if(
			opengl::lock_flag_read(
				lock_->method()
			)
		)
		{
			// this will only copy, not convert!
			sge::image::algorithm::copy_and_convert(
				view(),
				sge::image::view::make<
					view_type
				>(
					lock_->write_view_pointer(),
					lock_dim(),
					convert::format_to_color(
						format(),
						format_type()
					),
					optional_pitch()
				)
			);

			lock_->post_copy();
		}

		lock_->unlock();

		set_area(
			lock_area_
			?
				*lock_area_
			:
				lock_area(
					lock_area::vector::null(),
					dim()
				),
			lock_->write_pointer()
		);
	}

	lock_.reset();
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::lock_me(
	lock_area const &_lock_area,
	lock_method::type const _method
) const
{
	if(
		!opengl::range_check(
			dim(),
			_lock_area
		)
	)
		throw renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("ogl: lock (%1%) out of range! dim is %2%!")
				)
				% _lock_area
				% dim()
			).str()
		);

	lock_.take(
		opengl::create_texture_lock(
			context_,
			_method,
			dim().content(),
			_lock_area.area(),
			stride(),
			flags()
		)
	);

	bind();

	if(
		opengl::lock_flag_read(
			_method
		)
	)
		texfuncs::get_image(
			type(),
			format(),
			format_type(),
			lock_->read_pointer()
		);

	lock_->lock();

	if(
		_lock_area == this->area()
	)
		lock_area_.reset();
	else
		lock_area_ = _lock_area;
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::view_type const
sge::opengl::basic_texture<Base>::view()
{
	// if we are currently reading a texture,
	// we have mapped the whole texture and
	// have to take a sub view
	
	bool const reading(
		opengl::lock_flag_read(
			lock_->method()
		)
	);

	view_type const ret(
		image::view::make<
			view_type
		>(
			reading
			?
				lock_->read_view_pointer()
			:
				lock_->write_view_pointer(),
			reading
			?
				dim()
			:
				lock_dim(),
			convert::format_to_color(
				format(),
				format_type()
			),
			optional_pitch()
		)
	);

	return
		reading && lock_area_
		?
			sge::image::view::sub<
				view_type
			>(
				ret,
				*lock_area_
			)
		:
			ret;
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::const_view_type const
sge::opengl::basic_texture<Base>::view() const
{
	return
		image::view::to_const<
			const_view_type
		>(
			const_cast<
				basic_texture *
			>(
				this
			)->view()
		);
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::dim_type const
sge::opengl::basic_texture<Base>::lock_dim() const
{
	return
		lock_area_
		?
			lock_area_->dimension()
		:
			dim();
}

template<
	typename Base
>
sge::renderer::filter::texture const &
sge::opengl::basic_texture<Base>::filter() const
{
	return filter_;
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::size_type
sge::opengl::basic_texture<Base>::stride() const
{
	return stride_;
}

template<
	typename Base
>
GLenum
sge::opengl::basic_texture<Base>::format() const
{
	return format_;
}

template<
	typename Base
>
GLenum
sge::opengl::basic_texture<Base>::format_type() const
{
	return format_type_;
}

template<
	typename Base
>
GLenum
sge::opengl::basic_texture<Base>::internal_format() const
{
	return internal_format_;
}

template<
	typename Base
>
sge::opengl::basic_texture<Base>::basic_texture(
	opengl::context::object &_context,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags,
	GLenum const _type,
	image::color::format::type const _color_format,
	dim_type const &_dim
)
:
	texture_base(_type),
	context_(_context),
	filter_(_filter),
	flags_(_flags),
	dim_(_dim),
	format_(
		convert::color_to_format(
			_color_format
		)
	),
	format_type_(
		convert::color_to_format_type(
			_color_format
		)
	),
	internal_format_(
		convert::color_to_internal_format(
			_color_format
		)
	),
	stride_(
		image::color::format_stride(
			_color_format
		)
	),
	lock_(),
	lock_area_()
{
	bind();

	texfuncs::set_filter(
		context_,
		type(),
		filter()
	);
}

template<
	typename Base
>
sge::opengl::context::object &
sge::opengl::basic_texture<Base>::context() const
{
	return context_;
}

template<
	typename Base
>
sge::opengl::basic_texture<Base>::~basic_texture()
{
}

template<
	typename Base
>
sge::renderer::resource_flags_field const
sge::opengl::basic_texture<Base>::flags() const
{
	return flags_;
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::check_locked() const
{
	if(
		!lock_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl::basic_texture not locked!")
		);
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::check_not_locked() const
{
	if(
		lock_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl::basic_texture already locked!")
		);
}

#endif
