/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include "basic.hpp"
#include "create_lock.hpp"
#include "scoped_work_bind.hpp"
#include "funcs/get_image.hpp"
#include "funcs/set_filter.hpp"
#include "../convert/color_to_format.hpp"
#include "../convert/color_to_format_type.hpp"
#include "../convert/color_to_internal_format.hpp"
#include "../convert/format_to_color.hpp"
#include "../convert_lock_method.hpp"
#include "../lock_flag_read.hpp"
#include "../lock_flag_write.hpp"
#include "../range_check.hpp"
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/view/flipped.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/to_const.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/stage_type.hpp>
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
typename sge::opengl::texture::basic<Base>::dim_type const
sge::opengl::texture::basic<Base>::dim() const
{
	return dim_;
}

template<
	typename Base
>
typename sge::opengl::texture::basic<Base>::view_type const
sge::opengl::texture::basic<Base>::lock(
	lock_area const &_area,
	renderer::lock_mode::type const _mode
)
{
	this->lock_me(
		_area,
		opengl::convert_lock_method(
			_mode
		)
	);

	return this->view();
}

template<
	typename Base
>
typename sge::opengl::texture::basic<Base>::const_view_type const
sge::opengl::texture::basic<Base>::lock(
	lock_area const &_area
) const
{
	this->lock_me(
		_area,
		lock_method::readonly
	);

	return this->view();
}

template<
	typename Base
>
void
sge::opengl::texture::basic<Base>::unlock() const
{
	this->check_locked();

	lock_->pre_unlock();

	if(
		opengl::lock_flag_write(
			lock_->method()
		)
	)
	{
		// If this is also a read lock
		// we must copy the current view, which is
		// a slice into the whole texture retrieved,
		// to the destination buffer.
		if(
			opengl::lock_flag_read(
				lock_->method()
			)
		)
		{
			// this will only copy, not convert!
			sge::image::algorithm::copy_and_convert(
				this->view(),
				sge::image::view::make<
					view_type
				>(
					lock_->write_view_pointer(),
					this->lock_dim(),
					color_type_,
					optional_pitch()
				)
			);

			lock_->post_copy();
		}

		lock_->unlock();

		opengl::texture::scoped_work_bind const binding(
			context_,
			*this,
			renderer::stage_type(0u)
		);

		this->set_area(
			binding,
			lock_area_
			?
				*lock_area_
			:
				lock_area(
					lock_area::vector::null(),
					this->dim()
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
sge::opengl::texture::basic<Base>::lock_me(
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
		opengl::texture::create_lock(
			context_,
			_method,
			this->dim().content(),
			_lock_area.area(),
			this->stride(),
			this->flags()
		)
	);

	if(
		opengl::lock_flag_read(
			_method
		)
	)
	{
		opengl::texture::scoped_work_bind const binding(
			context_,
			*this,
			renderer::stage_type(0u)
		);

		opengl::texture::funcs::get_image(
			binding,
			this->type(),
			this->format(),
			this->format_type(),
			lock_->read_pointer(),
			renderer::stage_type(0u)
		);
	}

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
typename sge::opengl::texture::basic<Base>::view_type const
sge::opengl::texture::basic<Base>::view()
{
	// If we are currently reading a texture,
	// we have mapped the whole texture and
	// have to take a sub view.
	// Also, opengl reads the image flipped,
	// so we have to flip it too.
	
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
				this->dim()
			:
				this->lock_dim(),
			color_type_,
			optional_pitch()
		)
	);

	return
		reading && lock_area_
		?
			sge::image::view::flipped<
				view_type
			>(
				sge::image::view::sub<
					view_type
				>(
					ret,
					*lock_area_
				)
			)
		:
			ret;
}

template<
	typename Base
>
typename sge::opengl::texture::basic<Base>::const_view_type const
sge::opengl::texture::basic<Base>::view() const
{
	return
		image::view::to_const<
			const_view_type
		>(
			const_cast<
				opengl::texture::basic<Base> *
			>(
				this
			)->view()
		);
}

template<
	typename Base
>
typename sge::opengl::texture::basic<Base>::dim_type const
sge::opengl::texture::basic<Base>::lock_dim() const
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
sge::renderer::texture::filter::object const &
sge::opengl::texture::basic<Base>::filter() const
{
	return filter_;
}

template<
	typename Base
>
typename sge::opengl::texture::basic<Base>::size_type
sge::opengl::texture::basic<Base>::stride() const
{
	return stride_;
}

template<
	typename Base
>
sge::opengl::color_format const 
sge::opengl::texture::basic<Base>::format() const
{
	return format_;
}

template<
	typename Base
>
sge::opengl::color_format_type const
sge::opengl::texture::basic<Base>::format_type() const
{
	return format_type_;
}

template<
	typename Base
>
sge::opengl::internal_color_format const
sge::opengl::texture::basic<Base>::internal_format() const
{
	return internal_format_;
}

template<
	typename Base
>
sge::opengl::context::object &
sge::opengl::texture::basic<Base>::context() const
{
	return context_;
}

template<
	typename Base
>
sge::opengl::texture::basic<Base>::basic(
	opengl::context::object &_context,
	renderer::texture::filter::object const &_filter,
	renderer::resource_flags_field const &_flags,
	opengl::texture::type const _type,
	image::color::format::type const _color_format,
	dim_type const &_dim
)
:
	opengl::texture::base(_type),
	context_(_context),
	filter_(_filter),
	flags_(_flags),
	dim_(_dim),
	format_(
		opengl::convert::color_to_format(
			_color_format
		)
	),
	format_type_(
		opengl::convert::color_to_format_type(
			_color_format
		)
	),
	internal_format_(
		opengl::convert::color_to_internal_format(
			_color_format
		)
	),
	color_type_(
		opengl::convert::format_to_color(
			format_,
			format_type_
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
	opengl::texture::scoped_work_bind const binding(
		context_,
		*this,
		renderer::stage_type(0u)
	);

	opengl::texture::funcs::set_filter(
		binding,
		context_,
		this->type(),
		this->filter()
	);
}

template<
	typename Base
>
sge::opengl::texture::basic<Base>::~basic()
{
}

template<
	typename Base
>
sge::renderer::resource_flags_field const
sge::opengl::texture::basic<Base>::flags() const
{
	return flags_;
}

template<
	typename Base
>
void
sge::opengl::texture::basic<Base>::check_locked() const
{
	if(
		!lock_
	)
		throw renderer::exception(
			FCPPT_TEXT("opengl::texture::basic not locked!")
		);
}

template<
	typename Base
>
void
sge::opengl::texture::basic<Base>::check_not_locked() const
{
	if(
		lock_
	)
		throw renderer::exception(
			FCPPT_TEXT("opengl::texture::basic already locked!")
		);
}

#endif
