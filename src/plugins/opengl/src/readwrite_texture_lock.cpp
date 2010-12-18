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


#include "../readwrite_texture_lock.hpp"
#include <fcppt/container/raw_vector_impl.hpp>

sge::opengl::readwrite_texture_lock::readwrite_texture_lock(
	context::object &_context,
	size_type const _read_size,
	size_type const _write_size,
	size_type const _stride,
	renderer::resource_flags_field const &_flags
)
:
	read_lock_(
		_context,
		_read_size,
		_stride,
		_flags
	),
	write_lock_(
		_context,
	  	_write_size,
		_stride,
		_flags
	)
{
}

sge::opengl::readwrite_texture_lock::~readwrite_texture_lock()
{
}

void
sge::opengl::readwrite_texture_lock::lock()
{
	read_lock_.lock();
}

void
sge::opengl::readwrite_texture_lock::unlock()
{
	write_lock_.unlock();
}

void
sge::opengl::readwrite_texture_lock::pre_unlock()
{
	write_lock_.lock();
}

void
sge::opengl::readwrite_texture_lock::post_copy()
{
	read_lock_.unlock();
}

sge::opengl::readwrite_texture_lock::pointer
sge::opengl::readwrite_texture_lock::read_pointer()
{
	return read_lock_.read_pointer();
}

sge::opengl::readwrite_texture_lock::pointer
sge::opengl::readwrite_texture_lock::write_pointer()
{
	return write_lock_.write_pointer();
}

sge::opengl::readwrite_texture_lock::pointer
sge::opengl::readwrite_texture_lock::read_view_pointer()
{
	return read_lock_.read_view_pointer();
}

sge::opengl::readwrite_texture_lock::pointer
sge::opengl::readwrite_texture_lock::write_view_pointer()
{
	return write_lock_.write_view_pointer();
}

sge::opengl::lock_method::type
sge::opengl::readwrite_texture_lock::method() const
{
	return lock_method::readwrite;
}
