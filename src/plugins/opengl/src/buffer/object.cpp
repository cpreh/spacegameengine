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


#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/normal_lock_method.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/range_lock_method.hpp>
#include <sge/opengl/convert/resource_flags.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::opengl::buffer::object::object(
	sge::opengl::buffer::base &_base,
	size_type const _size,
	size_type const _stride,
	sge::renderer::resource_flags_field const &_flags,
	const_pointer const _src
)
:
	base_(
		_base
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
		nullptr
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
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer: cannot create an empty buffer!")
		);

	this->bind();

	base_.buffer_data(
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				new_size
			)
		),
		_src,
		sge::opengl::convert::resource_flags(
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
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): you have to unlock before locking!")
		);

	if(
		sge::renderer::lock_flags::read(
			_lockflags
		)
		&&
		!(
			this->flags()
			&
			sge::renderer::resource_flags::readable
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer: Cannot lock a writeonly buffer for reading!")
		);

	if(
		_first > this->size()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): first out of range!")
		);

	if(
		_count == npos
	)
		_count = this->size() - _first;

	if(
		_first + _count > this->size()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer::lock(): first + count > size()")
		);

	this->bind();

	if(
		_count < this->size()
		&&
		base_.map_buffer_range_supported()
	)
	{
		dest_ =
			fcppt::cast::from_void_ptr<
				pointer
			>(
				base_.map_buffer_range(
					sge::opengl::buffer::range_lock_method(
						_lockflags
					),
					fcppt::cast::size<
						GLsizei
					>(
						fcppt::cast::to_signed(
							_first
							*
							this->stride()
						)
					),
					fcppt::cast::size<
						GLsizei
					>(
						fcppt::cast::to_signed(
							_count
							*
							this->stride()
						)
					)
				)
			);

		lock_offset_ = 0;
	}
	else
	{
		dest_ =
			fcppt::cast::from_void_ptr<
				pointer
			>(
				base_.map_buffer(
					sge::opengl::buffer::normal_lock_method(
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
		dest_
		==
		nullptr
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer::unlock(), buffer is not locked! cannot unlock!")
		);

	this->bind();

	base_.unmap_buffer();

	dest_ = nullptr;

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
		_first + _count > this->size()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer::sub_data(), first + count out of range!")
		);

	if(
		dest_
		!=
		nullptr
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer::sub_data(), buffer must not be locked!")
		);

	this->bind();

	base_.buffer_sub_data(
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_first
				*
				this->stride()
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_count
				*
				this->stride()
			)
		),
		_data
	);
}

sge::opengl::buffer::object::size_type
sge::opengl::buffer::object::size() const
{
	return
		size_;
}

sge::opengl::buffer::object::size_type
sge::opengl::buffer::object::stride() const
{
	return
		stride_;
}

sge::renderer::resource_flags_field const &
sge::opengl::buffer::object::flags() const
{
	return
		flags_;
}

sge::opengl::buffer::object::pointer
sge::opengl::buffer::object::data()
{
	if(
		dest_
		==
		nullptr
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer used but the buffer has not been locked!")
		);

	return
		dest_ + lock_offset_;
}

sge::opengl::buffer::object::const_pointer
sge::opengl::buffer::object::data() const
{
	return
		const_cast<
			const_pointer
		>(
			const_cast<
				sge::opengl::buffer::object &
			>(
				*this
			).data()
		);
}

sge::opengl::buffer::object::size_type
sge::opengl::buffer::object::lock_size() const
{
	return
		lock_size_;
}

void
sge::opengl::buffer::object::unbind()
{
	this->bind_id(
		sge::opengl::buffer::optional_id()
	);
}

void
sge::opengl::buffer::object::bind() const
{
	this->bind_id(
		sge::opengl::buffer::optional_id(
			this->id()
		)
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
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl_buffer::buffer_offset used but the buffer has been locked!")
		);

	this->bind();

	return
		fcppt::cast::from_void_ptr<
			pointer
		>(
			base_.buffer_offset(
				fcppt::cast::size<
					GLsizei
				>(
					fcppt::cast::to_signed(
						_sz
						*
						this->stride()
					)
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
	return
		holder_.id();
}

bool
sge::opengl::buffer::object::native() const
{
	return
		base_.native();
}

void
sge::opengl::buffer::object::bind_id(
	sge::opengl::buffer::optional_id const &_id
) const
{
	base_.bind_buffer(
		_id
	);
}
