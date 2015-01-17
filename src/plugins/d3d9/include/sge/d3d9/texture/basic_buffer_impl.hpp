/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/make_pitch.hpp>
#include <sge/d3d9/convert/lock_flags.hpp>
#include <sge/d3d9/texture/basic_buffer.hpp>
#include <sge/d3d9/texture/buffer_size.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/renderer/basic_lock_box.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/optional_impl.hpp>


template<
	typename Types
>
sge::d3d9::texture::basic_buffer<
	Types
>::basic_buffer(
	d3d_buffer_create_function const &_buffer_create,
	sge::image::color::format const _color_format,
	sge::renderer::resource_flags_field const &_resource_flags
)
:
	buffer_create_(
		_buffer_create
	),
	color_format_(
		_color_format
	),
	resource_flags_(
		_resource_flags
	),
	size_(
		sge::d3d9::texture::buffer_size(
			*buffer_create_()
		)
	),
	buffer_(),
	locked_dest_()
{
}

template<
	typename Types
>
sge::d3d9::texture::basic_buffer<
	Types
>::~basic_buffer()
{
}

template<
	typename Types
>
typename sge::d3d9::texture::basic_buffer<
	Types
>::view const
sge::d3d9::texture::basic_buffer<
	Types
>::lock(
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
{
	return
		this->lock_impl<
			view
		>(
			sge::image::view::make<
				image_tag
			>,
			_area,
			sge::renderer::lock_flags::from_mode(
				_mode
			)
		);
}

template<
	typename Types
>
typename sge::d3d9::texture::basic_buffer<
	Types
>::const_view const
sge::d3d9::texture::basic_buffer<
	Types
>::lock(
	lock_area const &_area
) const
{
	return
		this->lock_impl<
			const_view
		>(
			sge::image::view::make_const<
				image_tag
			>,
			_area,
			sge::renderer::lock_flags::method::read
		);
}

template<
	typename Types
>
void
sge::d3d9::texture::basic_buffer<
	Types
>::unlock() const
{
	Types::unlock(
		*buffer_
	);

	buffer_.reset();

	locked_dest_.reset();
}

template<
	typename Types
>
typename sge::d3d9::texture::basic_buffer<
	Types
>::dim const
sge::d3d9::texture::basic_buffer<
	Types
>::size() const
{
	return
		size_;
}

template<
	typename Types
>
sge::image::color::format
sge::d3d9::texture::basic_buffer<
	Types
>::format() const
{
	return
		color_format_;
}

template<
	typename Types
>
template<
	typename View,
	typename MakeView
>
View const
sge::d3d9::texture::basic_buffer<
	Types
>::lock_impl(
	MakeView const &_make_view,
	lock_area const &_area,
	sge::renderer::lock_flags::method const _method
) const
{
	buffer_ =
		buffer_create_();

	typedef typename Types::lock_dest lock_dest;

	lock_dest const dest_rect(
		_area
		== this->area()
		?
			lock_dest()
		:
			lock_dest(
				_area
			)
	);

	sge::d3d9::lock_flags const lock_method(
		sge::d3d9::convert::lock_flags(
			_method,
			resource_flags_
		)
	);

	locked_dest_ =
		Types::lock(
			*buffer_,
			dest_rect,
			lock_method
		);

	return
		View(
			_make_view(
				static_cast<
					sge::image::raw_pointer
				>(
					locked_dest_->pBits
				),
				_area.size(),
				color_format_,
				sge::d3d9::make_pitch(
					*locked_dest_,
					_area.size(),
					color_format_
				)
			)
		);
}

#endif
