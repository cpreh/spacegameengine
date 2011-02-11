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


#include "../buffer.hpp"
#include "../common.hpp"
#include "../vbo_base.hpp"
#include "../lock_flag_read.hpp"
#include "../range_lock_method.hpp"
#include "../normal_lock_method.hpp"
#include "../convert/resource_flags.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::opengl::buffer::buffer(
	vbo_base &_vbo_base,
	GLenum const _type,
	size_type const _size,
	size_type const _stride,
	resource_flag_type const _flags,
	const_pointer const _src
)
:
	vbo_base_(_vbo_base),
	type_(_type),
	size_(_size),
	stride_(_stride),
	flags_(_flags),
	dest_(0),
	id_(vbo_base_.gen_buffer()),
	lock_offset_(0),
	lock_size_(0)
{
	size_type const nsz = size() * stride();

	if(nsz == 0)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer: cannot create an empty buffer!")
		);

	this->bind();

	vbo_base_.buffer_data(
		type_,
		static_cast<GLsizei>(nsz),
		_src,
		convert::resource_flags(
			flags()
		)
	);
}

sge::opengl::buffer::~buffer()
{
	if(dest_)
		unlock();

	unbind();

	vbo_base_.delete_buffer(
		id_
	);
}

void
sge::opengl::buffer::lock(
	lock_flag_type const _lockflags,
	size_type const _first,
	size_type _count
)
{
	if(dest_)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): you have to unlock before locking!")
		);

	if(
		opengl::lock_flag_read(_lockflags)
		&& !(flags() & renderer::resource_flags::readable)
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer: Cannot lock a writeonly buffer for reading!")
		);

	if(_first > size())
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): first out of range!")
		);

	if(_count == npos)
		_count = size() - _first;

	if(_first + _count > size())
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): first + count > size()")
		);

	this->bind();

	if(
		_count < size()
		&& vbo_base_.map_buffer_range_supported()
	)
	{
		dest_ =
			static_cast<
				pointer
			>(
				vbo_base_.map_buffer_range(
					type_,
					opengl::range_lock_method(
						_lockflags
					),
					static_cast<
						GLsizei
					>(
						_first * stride()
					),
					static_cast<
						GLsizei
					>(
						_count * stride()
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
				vbo_base_.map_buffer(
					type_,
					opengl::normal_lock_method(
						_lockflags
					)
				)
			);

		lock_offset_ = _first * stride();
	}

	lock_size_ = _count * stride();
}

void
sge::opengl::buffer::unlock()
{
	if(!dest_)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer::unlock(), buffer is not locked! cannot unlock!")
		);
	
	this->bind();

	vbo_base_.unmap_buffer(
		type_
	);

	dest_ = 0;

	lock_offset_ = lock_size_ = 0;
}


void
sge::opengl::buffer::sub_data(
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

	vbo_base_.buffer_sub_data(
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

sge::opengl::buffer::size_type
sge::opengl::buffer::size() const
{
	return size_;
}

sge::opengl::buffer::size_type
sge::opengl::buffer::stride() const
{
	return stride_;
}

sge::opengl::buffer::resource_flag_type
sge::opengl::buffer::flags() const
{
	return flags_;
}

sge::opengl::buffer::pointer
sge::opengl::buffer::data()
{
	if(
		!dest_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl_buffer used but the buffer has not been locked!")
		);

	return dest_ + lock_offset_;
}

sge::opengl::buffer::const_pointer
sge::opengl::buffer::data() const
{
	return
		const_cast<
			const_pointer
		>(
			const_cast<
				buffer &
			>(
				*this
			).data()
		);
}

sge::opengl::buffer::size_type
sge::opengl::buffer::lock_size() const
{
	return lock_size_;
}

void
sge::opengl::buffer::unbind()
{
	this->bind_id(
		0
	);
}

void
sge::opengl::buffer::bind() const
{
	this->bind_id(
		id_
	);
}

sge::opengl::buffer::pointer
sge::opengl::buffer::buffer_offset(
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
			vbo_base_.buffer_offset(
				type_,
				static_cast<
					GLsizei
				>(
					_sz * stride()
				)
			)
		);
}

sge::opengl::buffer::pointer
sge::opengl::buffer::raw_buffer() const
{
	return buffer_offset(0);
}

void
sge::opengl::buffer::bind_id(
	GLuint const _id
) const
{
	vbo_base_.bind_buffer(
		type_,
		_id
	);
}
