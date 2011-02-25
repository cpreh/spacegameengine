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
#include "../convert_vertices.hpp"
#include "../vbo_context.hpp"
#include "../convert_lock_method.hpp"
#include "../context/use.hpp"
#include "../vf/part.hpp"
#include <sge/renderer/vf/dynamic/view.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>

sge::opengl::vertex_buffer::vertex_buffer(
	context::object &_context,
	renderer::vf::dynamic::part_index const _part_index,
	renderer::vf::dynamic::part const &_format_part,
	size_type const _size,
	renderer::resource_flags_field const &_flags
)
:
	part_index_(_part_index),
	format_part_(_format_part),
	buffer_(
		context::use<
			vbo_context
		>(
			_context
		).impl(),
		context::use<
			vbo_context
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
	buffer_.lock(
		opengl::convert_lock_method(
			_flags
		),
		_offset,
		_range
	);

	return
		view_type(
			buffer_.data(),
			buffer_.lock_size(),
			this->format_part(),
			part_index_
		);
}

sge::opengl::vertex_buffer::const_view_type const
sge::opengl::vertex_buffer::lock(
	size_type const _offset,
	size_type const _range
) const
{
	buffer_.lock(
		lock_method::readonly,
		_offset,
		_range
	);

	return
		const_view_type(
			buffer_.data(),
			buffer_.lock_size(),
			this->format_part(),
			part_index_
		);
}

void
sge::opengl::vertex_buffer::unlock() const
{
	renderer::vf::dynamic::ordered_element_list const &elems(
		format_part_.elements()
	);

	renderer::size_type const stride(
		format_part_.stride()
	);

	FCPPT_ASSERT(
		buffer_.lock_size() % stride == 0
	);

	BOOST_FOREACH(
		renderer::vf::dynamic::ordered_element_list::const_reference elem,
		elems
	)
		opengl::convert_vertices(
			elem,
			stride,
			buffer_.lock_size() / stride,
			buffer_.data()
		);

	buffer_.unlock();
}

sge::opengl::vertex_buffer::size_type
sge::opengl::vertex_buffer::size() const
{
	return buffer_.size();
}

sge::renderer::resource_flags_field const
sge::opengl::vertex_buffer::flags() const
{
	return buffer_.flags();
}

sge::renderer::vf::dynamic::part const
sge::opengl::vertex_buffer::format_part() const
{
	return format_part_;
}
