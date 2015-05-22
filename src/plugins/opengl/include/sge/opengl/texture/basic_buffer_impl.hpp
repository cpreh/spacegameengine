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


#ifndef SGE_OPENGL_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/copy.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/traits/format_stride.hpp>
#include <sge/image/view/flipped.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/to_const.hpp>
#include <sge/opengl/range_check.hpp>
#include <sge/opengl/set_unpack_alignment.hpp>
#include <sge/opengl/stride_to_unpack_alignment.hpp>
#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/create_lock.hpp>
#include <sge/opengl/texture/get_level_size.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/funcs/get_image.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <sge/renderer/lock_flags/write.hpp>
#include <fcppt/const.hpp>
#include <fcppt/format.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/box/comparison.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/output.hpp>


template<
	typename Types
>
sge::opengl::texture::basic_buffer<
	Types
>::basic_buffer(
	format_type const _format,
	sge::opengl::texture::basic_buffer_parameters const &_parameters
)
:
	base_type(),
	sge::opengl::texture::buffer_base(
		_parameters.buffer_type(),
		_parameters.id(),
		_parameters.level()
	),
	system_context_(
		_parameters.system_context()
	),
	device_context_(
		_parameters.device_context()
	),
	type_(
		_parameters.type()
	),
	resource_flags_(
		_parameters.resource_flags()
	),
	size_(
		sge::opengl::texture::get_level_size<
			dim::dim_wrapper::value
		>(
			_parameters.binding(),
			_parameters.buffer_type(),
			_parameters.level()
		)
	),
	format_(
		_format
	),
	color_format_(
		_parameters.color_format()
	),
	color_format_type_(
		_parameters.color_format_type()
	),
	internal_color_format_(
		_parameters.internal_color_format()
	),
	is_render_target_(
		_parameters.is_render_target()
	),
	stride_(
		sge::image::traits::format_stride<
			color_tag
		>::execute(
			format_
		)
	),
	lock_(),
	lock_area_()
{
}

template<
	typename Types
>
sge::opengl::texture::basic_buffer<
	Types
>::~basic_buffer()
{
}

template<
	typename Types
>
sge::opengl::texture::is_render_target const
sge::opengl::texture::basic_buffer<
	Types
>::is_render_target() const
{
	return is_render_target_;
}

template<
	typename Types
>
typename sge::opengl::texture::basic_buffer<
	Types
>::dim const
sge::opengl::texture::basic_buffer<
	Types
>::size() const
{
	return size_;
}

template<
	typename Types
>
typename sge::opengl::texture::basic_buffer<
	Types
>::format_type
sge::opengl::texture::basic_buffer<
	Types
>::format() const
{
	return format_;
}

template<
	typename Types
>
typename sge::opengl::texture::basic_buffer<
	Types
>::view const
sge::opengl::texture::basic_buffer<
	Types
>::lock(
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
{
	this->lock_me(
		_area,
		sge::renderer::lock_flags::from_mode(
			_mode
		)
	);

	return this->lock_view();
}

template<
	typename Types
>
typename sge::opengl::texture::basic_buffer<
	Types
>::const_view const
sge::opengl::texture::basic_buffer<
	Types
>::lock(
	lock_area const &_area
) const
{
	this->lock_me(
		_area,
		sge::renderer::lock_flags::method::read
	);

	return
		this->lock_view();
}

template<
	typename Types
>
void
sge::opengl::texture::basic_buffer<
	Types
>::unlock() const
{
	this->check_locked();

	lock_->pre_unlock();

	if(
		sge::renderer::lock_flags::write(
			lock_->method()
		)
	)
	{
		// If this is also a read lock
		// we must copy the current view, which is
		// a slice into the whole texture retrieved,
		// to the destination buffer.
		if(
			sge::renderer::lock_flags::read(
				lock_->method()
			)
		)
		{
			// this will only copy, not convert!
			sge::image::algorithm::copy<
				image_tag
			>(
				this->lock_view(),
				sge::image::view::make<
					image_tag
				>(
					lock_->write_view_pointer(),
					this->lock_dim(),
					format_,
					basic_buffer::pitch::null()
				),
				sge::image::algorithm::may_overlap::no,
				sge::image::algorithm::uninitialized::yes
			);

			lock_->post_copy();
		}

		lock_->unlock();

		sge::opengl::texture::scoped_work_binding const binding(
			system_context_,
			device_context_,
			type_,
			this->id()
		);

		sge::opengl::set_unpack_alignment(
			device_context_,
			sge::opengl::stride_to_unpack_alignment(
				stride_
			)
		);

		Types::dim_types::sub_function()(
			binding,
			system_context_,
			this->buffer_type(),
			color_format_,
			color_format_type_,
			this->level(),
			this->size(),
			fcppt::from_optional(
				lock_area_,
				[
					this
				]{
					return
						lock_area(
							lock_area::vector::null(),
							this->size()
						);
				}
			),
			lock_->write_pointer()
		);
	}

	lock_.reset();
}

template<
	typename Types
>
void
sge::opengl::texture::basic_buffer<
	Types
>::lock_me(
	lock_area const &_lock_area,
	sge::renderer::lock_flags::method const _method
) const
{
	if(
		!sge::opengl::range_check(
			this->size(),
			_lock_area
		)
	)
		throw sge::renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("ogl: lock (%1%) out of range! dim is %2%!")
				)
				% _lock_area
				% this->size()
			).str()
		);

	lock_ =
		sge::opengl::texture::create_lock(
			system_context_,
			_method,
			this->content(),
			_lock_area.content(),
			stride_,
			resource_flags_
		);

	if(
		sge::renderer::lock_flags::read(
			_method
		)
	)
	{
		sge::opengl::texture::scoped_work_binding const binding(
			system_context_,
			device_context_,
			type_,
			this->id()
		);

		sge::opengl::texture::funcs::get_image(
			binding,
			this->buffer_type(),
			color_format_,
			color_format_type_,
			lock_->read_pointer(),
			this->level()
		);
	}

	lock_->lock();

	lock_area_ =
		_lock_area
		==
		this->area()
		?
			optional_lock_area()
		:
			optional_lock_area(
				_lock_area
			)
		;
}

template<
	typename Types
>
typename sge::opengl::texture::basic_buffer<
	Types
>::view const
sge::opengl::texture::basic_buffer<
	Types
>::lock_view()
{
	// If we are currently reading a texture, we have mapped the whole
	// texture and have to take a sub view. Also, opengl reads the image
	// flipped, so we have to flip it too.

	bool const reading(
		sge::renderer::lock_flags::read(
			lock_->method()
		)
	);

	view const ret(
		sge::image::view::make<
			image_tag
		>(
			reading
			?
				lock_->read_view_pointer()
			:
				lock_->write_view_pointer(),
			reading
			?
				this->size()
			:
				this->lock_dim(),
			format_,
			basic_buffer::pitch::null()
		)
	);

	return
		reading
		?
			fcppt::maybe(
				lock_area_,
				fcppt::const_(
					ret
				),
				[
					&ret
				](
					lock_area const &_area
				)
				{
					return
						sge::image::view::flipped<
							image_tag
						>(
							sge::image::view::sub<
								image_tag
							>(
								ret,
								_area
							)
						);
				}
			)
		:
			ret
		;
}

template<
	typename Types
>
typename sge::opengl::texture::basic_buffer<
	Types
>::const_view const
sge::opengl::texture::basic_buffer<
	Types
>::lock_view() const
{
	return
		sge::image::view::to_const<
			image_tag
		>(
			const_cast<
				sge::opengl::texture::basic_buffer<
					Types
				> *
			>(
				this
			)->lock_view()
		);
}

template<
	typename Types
>
typename sge::opengl::texture::basic_buffer<
	Types
>::dim const
sge::opengl::texture::basic_buffer<
	Types
>::lock_dim() const
{
	return
		fcppt::maybe(
			lock_area_,
			[
				this
			]{
				return
					this->size();
			},
			[](
				lock_area const &_area
			)
			{
				return
					_area.size();
			}
		);
}

template<
	typename Types
>
void
sge::opengl::texture::basic_buffer<
	Types
>::check_locked() const
{
	if(
		!lock_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("opengl::texture::basic_buffer not locked!")
		);
}

template<
	typename Types
>
void
sge::opengl::texture::basic_buffer<
	Types
>::check_not_locked() const
{
	if(
		lock_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("opengl::texture::basic_buffer already locked!")
		);
}

#endif
