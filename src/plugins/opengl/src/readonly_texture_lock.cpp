/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
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
#include <sge/raw_vector_impl.hpp>
#include <sge/algorithm.hpp>

sge::ogl::readonly_texture_lock::readonly_texture_lock(
	size_type const lock_size,
	size_type const offset,
	size_type const whole_size,
	size_type const stride,
	size_type const pitch,
	size_type const block_size,
	renderer::resource_flag_t const flags)
: buffer(
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
	buffer.lock(
		lock_method::readonly);
	if(pitch)
	{
		cutout_buffer.resize(
			lock_size);

		cutout_buffer_type::pointer dest(cutout_buffer.data());
		for(size_type i(offset); i < buffer.size(); i += pitch + block_size, dest += block_size)
			copy_n(buffer.data() + i, block_size, dest);
	}
}

void sge::ogl::readonly_texture_lock::pre_unlock()
{
	if(pitch)
	{
		pixel_pack_buffer::pointer dest(buffer.data());
		for(size_type i(0); i < cutout_buffer.size(); i += block_size, dest += pitch + block_size)
			copy_n(cutout_buffer.data() + i, block_size, dest);
	}
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
