/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/readonly_lock.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::texture::readonly_lock::readonly_lock(
	sge::opengl::context::object &_context,
	size_type const _whole_size,
	size_type const _stride,
	sge::renderer::resource_flags_field const &_flags
)
:
	buffer_(
		sge::opengl::context::use<
			sge::opengl::buffer::pbo_context
		>(
			_context,
			_context
		).pack_buffer(),
		_whole_size,
		_stride,
		_flags,
		nullptr
	)
{
}

sge::opengl::texture::readonly_lock::~readonly_lock()
{
}

void
sge::opengl::texture::readonly_lock::lock()
{
	buffer_.lock(
		this->method()
	);
}

void
sge::opengl::texture::readonly_lock::unlock()
{
	buffer_.unlock();
}

void
sge::opengl::texture::readonly_lock::pre_unlock()
{
}

void
sge::opengl::texture::readonly_lock::post_copy()
{
}

sge::opengl::texture::readonly_lock::pointer
sge::opengl::texture::readonly_lock::read_pointer()
{
	return
		buffer_.raw_buffer();
}

sge::opengl::texture::readonly_lock::pointer
sge::opengl::texture::readonly_lock::write_pointer()
{
	FCPPT_ASSERT_UNREACHABLE;
}

sge::opengl::texture::readonly_lock::pointer
sge::opengl::texture::readonly_lock::read_view_pointer()
{
	return
		buffer_.data();
}

sge::opengl::texture::readonly_lock::pointer
sge::opengl::texture::readonly_lock::write_view_pointer()
{
	FCPPT_ASSERT_UNREACHABLE;
}

sge::renderer::lock_flags::method
sge::opengl::texture::readonly_lock::method() const
{
	return
		sge::renderer::lock_flags::method::read;
}
