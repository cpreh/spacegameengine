/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/number_multiplexer/object.hpp>

namespace
{
sge::scenic::render_queue::sort_index
create_sort_index(
	sge::scenic::render_queue::index_type const _material,
	sge::scenic::render_queue::index_type const _vertex_buffer,
	sge::scenic::render_queue::index_type const _diffuse_texture,
	sge::scenic::render_queue::index_type const _specular_texture)
{
	typedef
	fcppt::number_multiplexer::object<sge::scenic::render_queue::sort_index>
	multiplexer;

	return
		multiplexer()
			.append(
				multiplexer::bit_count(
					20u),
				static_cast<sge::scenic::render_queue::sort_index>(
					_material))
			.append(
				multiplexer::bit_count(
					20u),
				static_cast<sge::scenic::render_queue::sort_index>(
					_vertex_buffer))
			.append(
				multiplexer::bit_count(
					10u),
				static_cast<sge::scenic::render_queue::sort_index>(
					_diffuse_texture))
			.append(
				multiplexer::bit_count(
					10u),
				static_cast<sge::scenic::render_queue::sort_index>(
					_specular_texture))
			.value();
}
}

sge::scenic::render_queue::mesh::mesh(
	sge::scenic::render_queue::index_type const _material,
	sge::scenic::render_queue::index_type const _vertex_buffer,
	sge::scenic::render_queue::index_type const _diffuse_texture,
	sge::scenic::render_queue::index_type const _specular_texture,
	sge::renderer::matrix4 const &_modelview,
	sge::renderer::index_buffer &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
:
	material_(
		_material),
	vertex_buffer_(
		_vertex_buffer),
	diffuse_texture_(
		_diffuse_texture),
	specular_texture_(
		_specular_texture),
	sort_index_(
		create_sort_index(
			_material,
			_vertex_buffer,
			_diffuse_texture,
			_specular_texture)),
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

sge::scenic::render_queue::index_type
sge::scenic::render_queue::mesh::diffuse_texture() const
{
	return
		diffuse_texture_;
}

sge::scenic::render_queue::index_type
sge::scenic::render_queue::mesh::specular_texture() const
{
	return
		specular_texture_;
}

sge::renderer::matrix4 const &
sge::scenic::render_queue::mesh::modelview() const
{
	return
		modelview_;
}

sge::renderer::index_buffer &
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
