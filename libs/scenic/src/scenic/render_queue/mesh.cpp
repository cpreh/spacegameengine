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


#include <sge/scenic/render_queue/mesh.hpp>
#include <sge/scenic/impl/number_multiplexer/object_impl.hpp>


namespace
{
sge::scenic::render_queue::sort_index
create_sort_index(
	sge::scenic::render_queue::index_type const _material,
	sge::scenic::render_queue::index_type const _vertex_buffer)
{
	typedef
	sge::scenic::impl::number_multiplexer::object<sge::scenic::render_queue::sort_index>
	multiplexer;

	return
		multiplexer()
			.append(
				multiplexer::bit_count(
					40u),
				static_cast<sge::scenic::render_queue::sort_index>(
					_material))
			.append(
				multiplexer::bit_count(
					20u),
				static_cast<sge::scenic::render_queue::sort_index>(
					_vertex_buffer))
			.value();
}
}

sge::scenic::render_queue::mesh::mesh(
	sge::scenic::render_queue::index_type const _material,
	sge::scenic::render_queue::index_type const _vertex_buffer,
	sge::renderer::matrix4 const &_modelview,
	sge::renderer::index::buffer &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
:
	material_(
		_material),
	vertex_buffer_(
		_vertex_buffer),
	sort_index_(
		create_sort_index(
			_material,
			_vertex_buffer)),
	modelview_(
		_modelview),
	index_buffer_(
		&_index_buffer),
	index_buffer_range_(
		_index_buffer_range)
{

}

sge::scenic::render_queue::index_type
sge::scenic::render_queue::mesh::material() const
{
	return
		material_;
}

sge::scenic::render_queue::index_type
sge::scenic::render_queue::mesh::vertex_buffer() const
{
	return
		vertex_buffer_;
}

sge::renderer::matrix4 const &
sge::scenic::render_queue::mesh::modelview() const
{
	return
		modelview_;
}

sge::renderer::index::buffer &
sge::scenic::render_queue::mesh::index_buffer() const
{
	return
		*index_buffer_;
}

sge::scenic::index_buffer_range const &
sge::scenic::render_queue::mesh::index_buffer_range() const
{
	return
		index_buffer_range_;
}
