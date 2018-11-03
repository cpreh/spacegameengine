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


#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/vbo_context.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/convert/index_format.hpp>
#include <sge/opengl/index/buffer.hpp>
#include <sge/renderer/dim1.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>


sge::opengl::index::buffer::buffer(
	sge::opengl::context::object &_context,
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
			_context,
			_context
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

sge::opengl::index::buffer::~buffer()
{
}

GLenum
sge::opengl::index::buffer::gl_format() const
{
	return
		gl_format_;
}

GLvoid *
sge::opengl::index::buffer::buffer_offset(
	sge::renderer::index::first const _size
) const
{
	return
		buffer_.buffer_offset(
			_size.get()
		);
}

void
sge::opengl::index::buffer::bind() const
{
	buffer_.bind();
}

sge::renderer::index::dynamic::view
sge::opengl::index::buffer::lock(
	sge::renderer::lock_segment const &_segment,
	sge::renderer::lock_mode const _flags
)
{
	return
		this->do_lock<
			sge::renderer::index::dynamic::view
		>(
			sge::renderer::lock_flags::from_mode(
				_flags
			),
			_segment
		);
}

sge::renderer::index::dynamic::const_view
sge::opengl::index::buffer::lock_c(
	sge::renderer::lock_segment const &_segment
) const
{
	return
		this->do_lock<
			sge::renderer::index::dynamic::const_view
		>(
			sge::renderer::lock_flags::method::read,
			_segment
		);
}

template<
	typename View
>
View
sge::opengl::index::buffer::do_lock(
	sge::renderer::lock_flags::method const _method,
	sge::renderer::lock_segment const &_segment
) const
{
	buffer_.lock(
		_method,
		_segment.pos().x(),
		_segment.size().w()
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
sge::opengl::index::buffer::unlock() const
{
	buffer_.unlock();
}

sge::renderer::dim1
sge::opengl::index::buffer::size() const
{
	return
		sge::renderer::dim1{
			buffer_.size()
		};
}

sge::renderer::resource_flags_field
sge::opengl::index::buffer::resource_flags() const
{
	return
		buffer_.flags();
}

sge::renderer::index::dynamic::format
sge::opengl::index::buffer::format() const
{
	return
		format_;
}

sge::opengl::buffer::object const &
sge::opengl::index::buffer::get() const
{
	return
		buffer_;
}
