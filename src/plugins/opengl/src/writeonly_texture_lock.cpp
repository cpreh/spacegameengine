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


#include "../writeonly_texture_lock.hpp"
#include "../pbo_context.hpp"
#include "../context/use.hpp"

sge::opengl::writeonly_texture_lock::writeonly_texture_lock(
	context::object &_context,
	size_type const _lock_size,
	size_type const _stride,
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
		).pixel_unpack_buffer_type(),
		_lock_size,
		_stride,
		_flags,
		0
	)
{
}

void
sge::opengl::writeonly_texture_lock::post_lock()
{
	buffer_.lock(
		lock_method::writeonly
	);
}

void
sge::opengl::writeonly_texture_lock::pre_unlock()
{
	buffer_.unlock();
}

sge::opengl::writeonly_texture_lock::pointer
sge::opengl::writeonly_texture_lock::write_pointer() const
{
	return buffer_.buffer_offset(0);
}

sge::opengl::writeonly_texture_lock::pointer
sge::opengl::writeonly_texture_lock::real_write_pointer()
{
	return buffer_.data();
}

sge::opengl::lock_method::type
sge::opengl::writeonly_texture_lock::method() const
{
	return lock_method::writeonly;
}
