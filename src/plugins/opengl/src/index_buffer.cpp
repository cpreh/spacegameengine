/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/index_buffer.hpp>
#include <sge/opengl/buffer/vbo_context.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/convert/index_format.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>


sge::opengl::index_buffer::index_buffer(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::index::buffer_parameters const &_parameters
)
:
	sge::renderer::index::buffer(),
	sge::opengl::buffer::wrapper(),
	format_(
		_parameters.format()
	),
	gl_format_(
		sge::opengl::convert::index_format(
			format_
		)
	),
	buffer_(
		sge::opengl::context::use<
			sge::opengl::buffer::vbo_context
		>(
			_system_context,
			_system_context
		).index_buffer(),
		_parameters.count().get(),
		sge::renderer::index::dynamic::format_stride(
			format_
		),
		_parameters.flags(),
		nullptr
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
	first_type const _size
) const
{
	return
		buffer_.buffer_offset(
			_size.get()
		);
}

void
sge::opengl::index_buffer::bind() const
{
	buffer_.bind();
}

sge::opengl::index_buffer::view_type const
sge::opengl::index_buffer::lock(
	sge::renderer::lock_mode const _flags,
	first_type const _offset,
	count_type const _range
)
{
	return
		this->do_lock<
			view_type
		>(
			sge::renderer::lock_flags::from_mode(
				_flags
			),
			_offset,
			_range
		);
}

sge::opengl::index_buffer::const_view_type const
sge::opengl::index_buffer::lock(
	first_type const _offset,
	count_type const _range
) const
{
	return
		this->do_lock<
			const_view_type
		>(
			renderer::lock_flags::method::read,
			_offset,
			_range
		);
}

template<
	typename View
>
View const
sge::opengl::index_buffer::do_lock(
	sge::renderer::lock_flags::method const _method,
	first_type const _offset,
	count_type const _range
) const
{
	buffer_.lock(
		_method,
		_offset.get(),
		_range.get()
	);

	return
		View(
			buffer_.data(),
			buffer_.lock_size()
			/
			sge::renderer::index::dynamic::format_stride(
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

sge::opengl::index_buffer::count_type const
sge::opengl::index_buffer::size() const
{
	return
		count_type(
			buffer_.size()
		);
}

sge::renderer::resource_flags_field const
sge::opengl::index_buffer::resource_flags() const
{
	return buffer_.flags();
}

sge::renderer::index::dynamic::format
sge::opengl::index_buffer::format() const
{
	return format_;
}

sge::opengl::buffer::object const &
sge::opengl::index_buffer::buffer() const
{
	return buffer_;
}
