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
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::readonly_texture_lock::readonly_texture_lock(
	size_type const lock_size,
	size_type const offset,
	size_type const whole_size,
	size_type const stride,
	size_type const pitch,
	renderer::resource_flag_t const flags)
: buffer(
	whole_size,
	stride,
	flags,
	0),
  offset(offset),
  stride(stride),
  pitch(pitch)
{}

void sge::ogl::readonly_texture_lock::post_lock()
{
	buffer.lock(
		lock_method::readonly);
	// FIXME: copy the stuff over in our buffer
}

void sge::ogl::readonly_texture_lock::pre_unlock()
{
	// FIXME: copy our buffer over in the lock_buffer
	buffer.unlock();
}

sge::ogl::readonly_texture_lock::pointer
sge::ogl::readonly_texture_lock::write_pointer() const
{
	throw exception(
		SGE_TEXT("Can't get a write pointer to a const lock!"));
}

sge::ogl::readonly_texture_lock::pointer
sge::ogl::readonly_texture_lock::read_pointer() const
{
	// FIXME: use our buffer instead
	return buffer.buffer_offset(offset * stride);
}

sge::ogl::lock_method::type
sge::ogl::readonly_texture_lock::method() const
{
	return lock_method::readonly;
}
