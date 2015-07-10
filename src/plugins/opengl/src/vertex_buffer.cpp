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


#include <sge/image/color/format.hpp>
#include <sge/opengl/vertex_buffer.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/vbo_context.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/vf/part.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>


sge::opengl::vertex_buffer::vertex_buffer(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::vf::dynamic::part_index const _part_index,
	sge::renderer::vf::dynamic::part const &_format_part,
	count_type const _size,
	sge::renderer::resource_flags_field const &_flags
)
:
	sge::renderer::vertex::buffer(),
	sge::opengl::buffer::wrapper(),
	part_index_(
		_part_index
	),
	format_part_(
		_format_part
	),
	converter_(
		format_part_,
		sge::renderer::vf::dynamic::color_format_vector{
			sge::image::color::format::rgba8,
			sge::image::color::format::rgba32f
		}
	),
	buffer_(
		sge::opengl::context::use<
			sge::opengl::buffer::vbo_context
		>(
			_system_context,
			_system_context
		).vertex_buffer(),
		_size.get(),
		_format_part.stride().get(),
		_flags,
		nullptr
	)
{
}

sge::opengl::vertex_buffer::~vertex_buffer()
{
}

void
sge::opengl::vertex_buffer::use(
	sge::opengl::vf::part const &_format_part
) const
{
	buffer_.bind();

	_format_part.use_me(
		buffer_.buffer_offset(
			0
		)
	);
}

void
sge::opengl::vertex_buffer::unuse(
	sge::opengl::vf::part const &_format_part
) const
{
	_format_part.unuse_me();
}

sge::opengl::vertex_buffer::view_type const
sge::opengl::vertex_buffer::lock(
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

sge::opengl::vertex_buffer::const_view_type const
sge::opengl::vertex_buffer::lock(
	first_type const _offset,
	count_type const _range
) const
{
	return
		this->do_lock<
			const_view_type
		>(
			sge::renderer::lock_flags::method::read,
			_offset,
			_range
		);
}

template<
	typename View
>
View const
sge::opengl::vertex_buffer::do_lock(
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

	converter_.lock(
		sge::renderer::vf::dynamic::locked_part(
			buffer_.data(),
			_offset,
			_range == npos
			?
				this->size()
			:
				_range
			,
			_method
		)
	);

	return
		View(
			buffer_.data(),
			count_type(
				buffer_.lock_size()
			),
			this->format_part(),
			part_index_
		);
}

void
sge::opengl::vertex_buffer::unlock() const
{
	converter_.unlock();

	buffer_.unlock();
}

sge::opengl::vertex_buffer::count_type const
sge::opengl::vertex_buffer::size() const
{
	return
		count_type(
			buffer_.size()
		);
}

sge::renderer::resource_flags_field const
sge::opengl::vertex_buffer::resource_flags() const
{
	return
		buffer_.flags();
}

sge::renderer::vf::dynamic::part const &
sge::opengl::vertex_buffer::format_part() const
{
	return
		format_part_;
}

sge::renderer::vf::dynamic::part_index const
sge::opengl::vertex_buffer::format_part_index() const
{
	return
		part_index_;
}

sge::opengl::buffer::object const &
sge::opengl::vertex_buffer::buffer() const
{
	return
		buffer_;
}
