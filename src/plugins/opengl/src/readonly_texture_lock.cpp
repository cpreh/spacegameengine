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


#include "../readonly_texture_lock.hpp"
#include <sge/container/raw_vector_impl.hpp>
#include <sge/algorithm/copy_n.hpp>
#include <sge/assert.hpp>

sge::ogl::readonly_texture_lock::readonly_texture_lock(
	size_type const lock_size,
	size_type const offset,
	size_type const whole_size,
	size_type const stride,
	size_type const pitch,
	size_type const block_size,
	renderer::resource_flag_t const flags)
:
	buffer(
		whole_size,
		stride,
		flags,
		0),
	lock_size(lock_size * stride),
	offset(offset * stride),
	pitch(pitch * stride),
	block_size(block_size * stride)
{}

void sge::ogl::readonly_texture_lock::post_lock()
{
	do_lock();

	if(!pitch)
		return;
	
	// if the pitch is set we copy the part to read
	// in our own buffer so that the user sees a contiguous array

	SGE_ASSERT(lock_size % block_size == 0);

	cutout_buffer.resize_uninitialized(
		lock_size);

	copy_read_part(cutout_buffer.data());
}

void sge::ogl::readonly_texture_lock::do_lock()
{
	buffer.lock(
		lock_method::readonly);
}

void sge::ogl::readonly_texture_lock::copy_read_part(
	pointer const dest) const
{
	size_type i(offset);
	for(pointer p(dest); p != dest + lock_size;
	    i += pitch + block_size, p += block_size)
		algorithm::copy_n(buffer.data() + i, block_size, p);
}

void sge::ogl::readonly_texture_lock::pre_unlock()
{
	buffer.unlock();
}

sge::ogl::readonly_texture_lock::pointer
sge::ogl::readonly_texture_lock::read_pointer() const
{
	return buffer.buffer_offset(0);
}

sge::ogl::readonly_texture_lock::const_pointer
sge::ogl::readonly_texture_lock::real_read_pointer() const
{
	return pitch
		? cutout_buffer.data()
		: read_pointer();
}

sge::ogl::lock_method::type
sge::ogl::readonly_texture_lock::method() const
{
	return lock_method::readonly;
}
