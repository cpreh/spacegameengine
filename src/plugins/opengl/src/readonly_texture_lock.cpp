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


#include "../readonly_texture_lock.hpp"
#include "../pbo_context.hpp"
#include "../context/use.hpp"
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/assert.hpp>

sge::opengl::readonly_texture_lock::readonly_texture_lock(
	context::object &_context,
	size_type const _lock_size,
	size_type const _offset,
	size_type const _whole_size,
	size_type const _stride,
	size_type const _pitch,
	size_type const _block_size,
	renderer::resource_flags_field const &_flags
)
:
	buffer_(
		context::use<
			pbo_context
		>(
			_context
		).impl(),
		context::use<
			pbo_context
		>(
			_context
		).pixel_pack_buffer_type(),
		_whole_size,
		_stride,
		_flags,
		0
	),
	lock_size_(
		_lock_size * _stride
	),
	offset_(
		_offset * _stride
	),
	pitch_(
		_pitch * _stride
	),
	block_size_(
		_block_size * _stride
	)
{}

void
sge::opengl::readonly_texture_lock::post_lock()
{
	do_lock();

	if(!pitch_)
		return;

	// if the pitch is set we copy the part to read
	// in our own buffer so that the user sees a contiguous array

	FCPPT_ASSERT(
		lock_size_ % block_size_ == 0
	);

	cutout_buffer_.resize_uninitialized(
		lock_size_
	);

	copy_read_part(
		cutout_buffer_.data()
	);
}

void
sge::opengl::readonly_texture_lock::do_lock()
{
	buffer_.lock(
		lock_method::readonly
	);
}

void
sge::opengl::readonly_texture_lock::copy_read_part(
	pointer const dest
) const
{
	size_type i(offset_);

	for(
		pointer p(dest);
		p != dest + lock_size_;
		i += pitch_ + block_size_, p += block_size_
	)
		fcppt::algorithm::copy_n(
			buffer_.data() + i,
			block_size_,
			p
		);
}

void
sge::opengl::readonly_texture_lock::pre_unlock()
{
	buffer_.unlock();
}

sge::opengl::readonly_texture_lock::pointer
sge::opengl::readonly_texture_lock::read_pointer() const
{
	return buffer_.buffer_offset(0);
}

sge::opengl::readonly_texture_lock::const_pointer
sge::opengl::readonly_texture_lock::real_read_pointer() const
{
	return pitch_
		? cutout_buffer_.data()
		: read_pointer();
}

sge::opengl::lock_method::type
sge::opengl::readonly_texture_lock::method() const
{
	return lock_method::readonly;
}
