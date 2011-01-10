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
#include "../context/use.hpp"
#include "../convert_vertices.hpp"
#include "../vbo_context.hpp"
#include "../convert_lock_method.hpp"
#include <sge/renderer/vf/dynamic/view.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>

sge::opengl::vertex_buffer::vertex_buffer(
	context::object &_context,
	renderer::vf::dynamic::format const &_format,
	size_type const _size,
	renderer::resource_flags_field const &_flags
)
:
	format_(
		_context,
		_format
	),
	buf(
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
		_format.stride(),
		_flags,
		0
	)
{}

void
sge::opengl::vertex_buffer::set_format() const
{
	buf.bind_me();

	format_.use_me(
		buf.buffer_offset(
			0
		)
	);
}

void
sge::opengl::vertex_buffer::unset_format() const
{
	format_.unuse_me();
}

sge::opengl::vertex_buffer::view_type const
sge::opengl::vertex_buffer::lock(
	renderer::lock_mode::type const _flags,
	size_type const _offset,
	size_type const _range
)
{
	buf.lock(
		opengl::convert_lock_method(
			_flags
		),
		_offset,
		_range
	);

	return
		view_type(
			buf.data(),
			buf.lock_size(),
			format()
		);
}

sge::opengl::vertex_buffer::const_view_type const
sge::opengl::vertex_buffer::lock(
	size_type const _offset,
	size_type const _range
) const
{
	buf.lock(
		lock_method::readonly,
		_offset,
		_range
	);

	return
		const_view_type(
			buf.data(),
			buf.lock_size(),
			format()
		);
}

void
sge::opengl::vertex_buffer::unlock() const
{
	renderer::vf::dynamic::ordered_element_list const &elems(
		format().elements()
	);

	renderer::size_type const stride(
		format().stride()
	);

	FCPPT_ASSERT(buf.lock_size() % stride == 0);

	BOOST_FOREACH(
		renderer::vf::dynamic::ordered_element_list::const_reference elem,
		elems
	)
		opengl::convert_vertices(
			elem,
			stride,
			buf.lock_size() / stride,
			buf.data()
		);

	buf.unlock();
}

sge::opengl::vertex_buffer::size_type
sge::opengl::vertex_buffer::size() const
{
	return buf.size();
}

sge::renderer::resource_flags_field const
sge::opengl::vertex_buffer::flags() const
{
	return buf.flags();
}

sge::renderer::vf::dynamic::format const &
sge::opengl::vertex_buffer::format() const
{
	return format_.get();
}
