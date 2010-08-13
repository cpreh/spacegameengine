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


#include "../buffer.hpp"
#include "../common.hpp"
#include "../vbo_base.hpp"
#include "../lock_method.hpp"
#include "../convert/resource_flags.hpp"
#include <sge/exception.hpp>
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
		throw exception(
			FCPPT_TEXT("ogl_buffer: cannot create an empty buffer!")
		);

	bind_me();

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
	lock_flag_type const lockflags,
	size_type const first,
	size_type count
)
{
	if(dest_)
		throw exception(
			FCPPT_TEXT("ogl_buffer::lock(): you have to unlock before locking!")
		);

	if(
		lock_flag_read(lockflags)
		&& !(flags() & renderer::resource_flags::readable)
	)
		throw exception(
			FCPPT_TEXT("ogl_buffer: Cannot lock a writeonly buffer for reading!")
		);

	if(first > size())
		throw exception(
			FCPPT_TEXT("ogl_buffer::lock(): first out of range!")
		);

	if(count == npos)
		count = size() - first;

	if(first + count > size())
		throw exception(
			FCPPT_TEXT("ogl_buffer::lock(): first + count > size()")
		);

	bind_me();

	if(
		count < size()
		&& vbo_base_.map_buffer_range_supported()
	)
	{
		dest_ =
			static_cast<
				pointer
			>(
				vbo_base_.map_buffer_range(
					type_,
					range_lock_method(
						lockflags
					),
					static_cast<
						GLsizei
					>(
						first * stride()
					),
					static_cast<
						GLsizei
					>(
						count * stride()
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
					normal_lock_method(
						lockflags
					)
				)
			);

		lock_offset_ = first * stride();
	}

	lock_size_ = count * stride();
}

void
sge::opengl::buffer::unlock()
{
	if(!dest_)
		throw exception(
			FCPPT_TEXT("ogl_buffer::unlock(), buffer is not locked! cannot unlock!")
		);
	
	bind_me();

	vbo_base_.unmap_buffer(
		type_
	);

	dest_ = 0;

	lock_offset_ = lock_size_ = 0;
}


void
sge::opengl::buffer::sub_data(
	const_pointer const data,
	size_type const first,
	size_type const count
)
{
	if(
		first + count > size()
	)
		throw exception(
			FCPPT_TEXT("ogl_buffer::sub_data(), first + count out of range!")
		);

	if(
		dest_
	)
		throw exception(
			FCPPT_TEXT("ogl_buffer::sub_data(), buffer must not be locked!")
		);

	bind_me();

	vbo_base_.buffer_sub_data(
		type_,
		static_cast<
			GLsizei
		>(
			first * stride()
		),
		static_cast<
			GLsizei
		>(
			count * stride()
		),
		data
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
	check_lock();

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
sge::opengl::buffer::bind(
	GLuint const _id
) const
{
	vbo_base_.bind_buffer(
		type_,
		_id
	);
}

void
sge::opengl::buffer::unbind()
{
	bind(0);
}

void
sge::opengl::buffer::bind_me() const
{
	bind(id_);
}

sge::opengl::buffer::pointer
sge::opengl::buffer::buffer_offset(
	size_type const sz
) const
{
	bind_me();

	return
		static_cast<
			pointer
		>(
			vbo_base_.buffer_offset(
				type_,
				static_cast<
					GLsizei
				>(
					sz * stride()
				)
			)
		);
}

void
sge::opengl::buffer::check_lock() const
{
	if(!dest_)
		throw exception(
			FCPPT_TEXT("ogl_buffer used but the buffer has not been locked!")
		);
}
