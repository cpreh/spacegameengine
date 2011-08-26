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


#include "../vertex_buffer.hpp"
#include "../buffer/vbo_context.hpp"
#include "../context/use.hpp"
#include "../vf/part.hpp"
#include <sge/image/color/format.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>

sge::opengl::vertex_buffer::vertex_buffer(
	context::object &_context,
	renderer::vf::dynamic::part_index const _part_index,
	renderer::vf::dynamic::part const &_format_part,
	size_type const _size,
	renderer::resource_flags_field const &_flags
)
:
	sge::renderer::vertex_buffer(),
	opengl::buffer::wrapper(),
	part_index_(_part_index),
	format_part_(_format_part),
	converter_(
		format_part_,
		fcppt::assign::make_container<
			sge::renderer::vf::dynamic::color_format_vector
		>(
			sge::image::color::format::rgba8
		)
		(
			sge::image::color::format::rgba32f
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
		).vertex_buffer_type(),
		_size,
		_format_part.stride(),
		_flags,
		0
	)
{
}

sge::opengl::vertex_buffer::~vertex_buffer()
{
}

void
sge::opengl::vertex_buffer::use(
	opengl::vf::part const &_format_part
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
	opengl::vf::part const &_format_part
) const
{
	_format_part.unuse_me();
}

sge::opengl::vertex_buffer::view_type const
sge::opengl::vertex_buffer::lock(
	renderer::lock_mode::type const _flags,
	size_type const _offset,
	size_type const _range
)
{
	return
		this->do_lock<
			view_type
		>(
			renderer::lock_flags::from_mode(
				_flags
			),
			_offset,
			_range
		);
}

sge::opengl::vertex_buffer::const_view_type const
sge::opengl::vertex_buffer::lock(
	size_type const _offset,
	size_type const _range
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
sge::opengl::vertex_buffer::do_lock(
	renderer::lock_flags::method::type const _method,
	size_type const _offset,
	size_type const _range
) const
{
	buffer_.lock(
		_method,
		_offset,
		_range
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
			buffer_.lock_size(),
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

sge::opengl::vertex_buffer::size_type
sge::opengl::vertex_buffer::size() const
{
	return buffer_.size();
}

sge::renderer::resource_flags_field const
sge::opengl::vertex_buffer::resource_flags() const
{
	return buffer_.flags();
}

sge::renderer::vf::dynamic::part const
sge::opengl::vertex_buffer::format_part() const
{
	return format_part_;
}

sge::renderer::vf::dynamic::part_index const
sge::opengl::vertex_buffer::format_part_index() const
{
	return part_index_;
}

sge::opengl::buffer::object const &
sge::opengl::vertex_buffer::buffer() const
{
	return buffer_;
}
