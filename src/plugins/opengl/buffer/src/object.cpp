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


#include "../object.hpp"
#include "../base.hpp"
#include "../normal_lock_method.hpp"
#include "../range_lock_method.hpp"
#include "../../common.hpp"
#include "../../convert/resource_flags.hpp"
#include <sge/renderer/lock_flags/read.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::opengl::buffer::object::object(
	buffer::base &_base,
	GLenum const _type,
	size_type const _size,
	size_type const _stride,
	resource_flag_type const _flags,
	const_pointer const _src
)
:
	base_(
		_base
	),
	type_(
		_type
	),
	size_(
		_size
	),
	stride_(
		_stride
	),
	flags_(
		_flags
	),
	dest_(
		0
	),
	holder_(
		base_
	),
	lock_offset_(
		0
	),
	lock_size_(
		0
	)
{
	size_type const new_size(
		this->size()
		*
		this->stride()
	);

	if(
		new_size == 0
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer: cannot create an empty buffer!")
		);

	this->bind();

	base_.buffer_data(
		type_,
		static_cast<
			GLsizei
		>(
			new_size
		),
		_src,
		opengl::convert::resource_flags(
			this->flags()
		)
	);
}

sge::opengl::buffer::object::~object()
{
	if(
		dest_
	)
		this->unlock();

	this->unbind();
}

void
sge::opengl::buffer::object::lock(
	lock_flag_type const &_lockflags,
	size_type const _first,
	size_type _count
)
{
	if(
		dest_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): you have to unlock before locking!")
		);

	if(
		renderer::lock_flags::read(
			_lockflags
		)
		&&
		!(
			this->flags()
			& renderer::resource_flags::readable
		)
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer: Cannot lock a writeonly buffer for reading!")
		);

	if(
		_first > this->size()
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): first out of range!")
		);

	if(
		_count == npos
	)
		_count = this->size() - _first;

	if(
		_first + _count > this->size()
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): first + count > size()")
		);

	this->bind();

	if(
		_count < this->size()
		&& base_.map_buffer_range_supported()
	)
	{
		dest_ =
			static_cast<
				pointer
			>(
				base_.map_buffer_range(
					type_,
					opengl::buffer::range_lock_method(
						_lockflags
					),
					static_cast<
						GLsizei
					>(
						_first * this->stride()
					),
					static_cast<
						GLsizei
					>(
						_count * this->stride()
					)
				)
			);

		lock_offset_ = 0;
	}
	else
	{
		dest_ =
			static_cast<
				pointer
			>(
				base_.map_buffer(
					type_,
					opengl::buffer::normal_lock_method(
						_lockflags
					)
				)
			);

		lock_offset_ = _first * stride();
	}

	lock_size_ = _count * stride();
}

void
sge::opengl::buffer::object::unlock()
{
	if(
		!dest_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::unlock(), buffer is not locked! cannot unlock!")
		);

	this->bind();

	base_.unmap_buffer(
		type_
	);

	dest_ = 0;

	lock_offset_ = lock_size_ = 0;
}


void
sge::opengl::buffer::object::sub_data(
	const_pointer const _data,
	size_type const _first,
	size_type const _count
)
{
	if(
		_first + _count > size()
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::sub_data(), first + count out of range!")
		);

	if(
		dest_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::sub_data(), buffer must not be locked!")
		);

	this->bind();

	base_.buffer_sub_data(
		type_,
		static_cast<
			GLsizei
		>(
			_first * stride()
		),
		static_cast<
			GLsizei
		>(
			_count * stride()
		),
		_data
	);
}

sge::opengl::buffer::object::size_type
sge::opengl::buffer::object::size() const
{
	return size_;
}

sge::opengl::buffer::object::size_type
sge::opengl::buffer::object::stride() const
{
	return stride_;
}

sge::opengl::buffer::object::resource_flag_type
sge::opengl::buffer::object::flags() const
{
	return flags_;
}

sge::opengl::buffer::object::pointer
sge::opengl::buffer::object::data()
{
	if(
		!dest_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer used but the buffer has not been locked!")
		);

	return dest_ + lock_offset_;
}

sge::opengl::buffer::object::const_pointer
sge::opengl::buffer::object::data() const
{
	return
		const_cast<
			const_pointer
		>(
			const_cast<
				buffer::object &
			>(
				*this
			).data()
		);
}

sge::opengl::buffer::object::size_type
sge::opengl::buffer::object::lock_size() const
{
	return lock_size_;
}

void
sge::opengl::buffer::object::unbind()
{
	this->bind_id(
		buffer::id(
			0
		)
	);
}

void
sge::opengl::buffer::object::bind() const
{
	this->bind_id(
		this->id()
	);
}

sge::opengl::buffer::object::pointer
sge::opengl::buffer::object::buffer_offset(
	size_type const _sz
) const
{
	if(
		dest_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::buffer_offset used but the buffer has been locked!")
		);

	this->bind();

	return
		static_cast<
			pointer
		>(
			base_.buffer_offset(
				type_,
				static_cast<
					GLsizei
				>(
					_sz * stride()
				)
			)
		);
}

sge::opengl::buffer::object::pointer
sge::opengl::buffer::object::raw_buffer() const
{
	return
		this->buffer_offset(
			0
		);
}

sge::opengl::buffer::id const
sge::opengl::buffer::object::id() const
{
	return holder_.id();
}

bool
sge::opengl::buffer::object::native() const
{
	return base_.hardware_supported();
}

void
sge::opengl::buffer::object::bind_id(
	buffer::id const _id
) const
{
	base_.bind_buffer(
		type_,
		_id
	);
}
