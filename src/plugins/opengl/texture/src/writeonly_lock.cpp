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


#include "../writeonly_lock.hpp"
#include "../../pbo_context.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::texture::writeonly_lock::writeonly_lock(
	context::object &_context,
	size_type const _lock_size,
	size_type const _stride,
	renderer::resource_flags_field const &_flags
)
:
	buffer_(
		context::use<
			opengl::pbo_context
		>(
			_context
		).impl(),
		context::use<
			opengl::pbo_context
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

sge::opengl::texture::writeonly_lock::~writeonly_lock()
{
}

void
sge::opengl::texture::writeonly_lock::lock()
{
	buffer_.lock(
		this->method()
	);
}

void
sge::opengl::texture::writeonly_lock::unlock()
{
	buffer_.unlock();
}

void
sge::opengl::texture::writeonly_lock::pre_unlock()
{
}

void
sge::opengl::texture::writeonly_lock::post_copy()
{
}

sge::opengl::texture::writeonly_lock::pointer
sge::opengl::texture::writeonly_lock::read_pointer()
{
	throw sge::renderer::exception(
		FCPPT_TEXT("No read_pointer in writeonly_texture_lock!")
	);
}

sge::opengl::texture::writeonly_lock::pointer
sge::opengl::texture::writeonly_lock::write_pointer()
{
	return buffer_.raw_buffer();
}

sge::opengl::texture::writeonly_lock::pointer
sge::opengl::texture::writeonly_lock::read_view_pointer()
{
	throw sge::renderer::exception(
		FCPPT_TEXT("No read_view_pointer in writeonly_texture_lock!")
	);
}

sge::opengl::texture::writeonly_lock::pointer
sge::opengl::texture::writeonly_lock::write_view_pointer()
{
	return buffer_.data();
}

sge::renderer::lock_flags::method::type
sge::opengl::texture::writeonly_lock::method() const
{
	return renderer::lock_flags::method::write;
}
