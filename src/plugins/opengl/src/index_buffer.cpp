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


#include "../index_buffer.hpp"
#include "../common.hpp"
#include "../buffer/vbo_context.hpp"
#include "../context/use.hpp"
#include "../convert/index_format.hpp"
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <sge/renderer/index/dynamic/view.hpp>

sge::opengl::index_buffer::index_buffer(
	context::object &_context,
	renderer::index::dynamic::format::type const _format,
	size_type const _size,
	renderer::resource_flags_field const &_flags
)
:
	sge::renderer::index_buffer(),
	opengl::buffer::wrapper(),
	format_(_format),
	gl_format_(
		opengl::convert::index_format(
			_format
		)
	),
	buffer_(
		context::use<
			opengl::buffer::vbo_context
		>(
			_context
		).impl(),
		context::use<
			opengl::buffer::vbo_context
		>(
			_context
		).index_buffer_type(),
		_size,
		renderer::index::dynamic::format_stride(
			_format
		),
		_flags,
		0
	)
{
}

sge::opengl::index_buffer::~index_buffer()
{
}

GLenum
sge::opengl::index_buffer::gl_format() const
{
	return gl_format_;
}

GLvoid *
sge::opengl::index_buffer::buffer_offset(
	size_type const _size
) const
{
	return
		buffer_.buffer_offset(
			_size
		);
}

void
sge::opengl::index_buffer::bind() const
{
	buffer_.bind();
}

sge::opengl::index_buffer::view_type const
sge::opengl::index_buffer::lock(
	renderer::lock_mode::type const _flags,
	size_type const _offset,
	size_type const _range
)
{
	buffer_.lock(
		renderer::lock_flags::from_mode(
			_flags
		),
		_offset,
		_range
	);

	return
		view_type(
			buffer_.data(),
			buffer_.lock_size()
			/
			renderer::index::dynamic::format_stride(
				format_
			),
			format_
		);
}

sge::opengl::index_buffer::const_view_type const
sge::opengl::index_buffer::lock(
	size_type const _offset,
	size_type const _range
) const
{
	buffer_.lock(
		renderer::lock_flags::method::read,
		_offset,
		_range
	);

	return
		const_view_type(
			buffer_.data(),
			buffer_.lock_size()
			/
			renderer::index::dynamic::format_stride(
				format_
			),
			format_
		);
}

void
sge::opengl::index_buffer::unlock() const
{
	buffer_.unlock();
}

sge::opengl::index_buffer::size_type
sge::opengl::index_buffer::size() const
{
	return buffer_.size();
}

sge::renderer::resource_flags_field const
sge::opengl::index_buffer::resource_flags() const
{
	return buffer_.flags();
}

sge::renderer::index::dynamic::format::type
sge::opengl::index_buffer::format() const
{
	return format_;
}

sge::opengl::buffer::object const &
sge::opengl::index_buffer::buffer() const
{
	return buffer_;
}
