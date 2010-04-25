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


#include "../writeonly_texture_lock.hpp"

sge::opengl::writeonly_texture_lock::writeonly_texture_lock(
	size_type const lock_size,
	size_type const stride,
	renderer::resource_flags_field const &flags
)
:
	buffer(
		lock_size,
		stride,
		flags,
		0
	)
{
}

void
sge::opengl::writeonly_texture_lock::post_lock()
{
	buffer.lock(
		lock_method::writeonly
	);
}

void
sge::opengl::writeonly_texture_lock::pre_unlock()
{
	buffer.unlock();
}

sge::opengl::writeonly_texture_lock::pointer
sge::opengl::writeonly_texture_lock::write_pointer() const
{
	return buffer.buffer_offset(0);
}

sge::opengl::writeonly_texture_lock::pointer
sge::opengl::writeonly_texture_lock::real_write_pointer()
{
	return buffer.data();
}

sge::opengl::lock_method::type
sge::opengl::writeonly_texture_lock::method() const
{
	return lock_method::writeonly;
}
