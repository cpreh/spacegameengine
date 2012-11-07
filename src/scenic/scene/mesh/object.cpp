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


#include <sge/model/obj/prototype.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/scenic/scene/mesh/object.hpp>
#include <sge/scenic/vf/format.hpp>
#include <sge/scenic/vf/format_part.hpp>
#include <sge/scenic/vf/normal.hpp>
#include <sge/scenic/vf/position.hpp>
#include <sge/scenic/vf/texcoord.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::scenic::scene::mesh::object::object(
	sge::renderer::device::core &_renderer,
	sge::renderer::vertex_declaration &_vertex_declaration,
	sge::model::obj::prototype const &_prototype)
:
	vertex_buffer_(
		_renderer.create_vertex_buffer(
			_vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index
			<
				sge::scenic::vf::format,
				sge::scenic::vf::format_part
			>(),
			sge::renderer::vertex_count(
				static_cast<sge::renderer::size_type>(
					_prototype.face_vertices().size())),
			sge::renderer::resource_flags_field::null())),
	index_buffer_(
		_renderer.create_index_buffer(
			sge::renderer::index::dynamic::format::i32,
			sge::renderer::index_count(
				_prototype.face_count() * 3u),
			sge::renderer::resource_flags_field::null())),
	parts_(),
	bounding_box_(
		_prototype.bounding_box())
{
	this->fill_vertex_buffer(
		_prototype);

	this->fill_index_buffer(
		_prototype);
}

sge::renderer::vertex_buffer &
sge::scenic::scene::mesh::object::vertex_buffer()
{
	return
		*vertex_buffer_;
}

sge::renderer::index_buffer &
sge::scenic::scene::mesh::object::index_buffer()
{
	return
		*index_buffer_;
}

sge::scenic::scene::mesh::material_to_index_buffer_range const &
sge::scenic::scene::mesh::object::parts()
{
	return
		parts_;
}

sge::scenic::box const &
sge::scenic::scene::mesh::object::bounding_box() const
{
	return
		bounding_box_;
}

sge::scenic::scene::mesh::object::~object()
{
}

void
sge::scenic::scene::mesh::object::fill_vertex_buffer(
	sge::model::obj::prototype const &_prototype)
{
	sge::renderer::scoped_vertex_lock const vblock(
		*vertex_buffer_,
		sge::renderer::lock_mode::writeonly);

	typedef
	sge::renderer::vf::view<sge::scenic::vf::format_part>
	format_part_view;

	format_part_view const current_vertex_view(
		vblock.value());

	format_part_view::iterator current_vertex(
		current_vertex_view.begin());

	sge::model::obj::vertex_coordinate_sequence const &vertex_coordinates(
		_prototype.vertex_coordinates());

	sge::model::obj::texture_coordinate_sequence const &texture_coordinates(
		_prototype.texture_coordinates());

	sge::model::obj::normal_sequence const &normals(
		_prototype.normals());

	for(
		sge::model::obj::face_vertex_sequence::const_iterator current_face_vertex =
			_prototype.face_vertices().begin();
		current_face_vertex != _prototype.face_vertices().end();
		++current_face_vertex)
	{
		(*current_vertex).set<sge::scenic::vf::position>(
			vertex_coordinates[
				current_face_vertex->vertex_coordinate_index().get()]);

		(*current_vertex).set<sge::scenic::vf::texcoord>(
			texture_coordinates[
				current_face_vertex->texture_coordinate_index().get()]);

		(*current_vertex++).set<sge::scenic::vf::normal>(
			normals[
				current_face_vertex->normal_index().get()]);
	}
}

void
sge::scenic::scene::mesh::object::fill_index_buffer(
	sge::model::obj::prototype const &_prototype)
{
	sge::renderer::scoped_index_lock const iblock(
		*index_buffer_,
		sge::renderer::lock_mode::writeonly);

	// then we create a dynamic view to the buffer...
	sge::renderer::index::dynamic::view const indices(
		iblock.value());

	// ...then we declare an iterator for the buffer. Again, you we meet
	// the index format. We could have designed the following code to be
	// agnostic of the integer type, but that would be even more code.
	sge::renderer::index::iterator<sge::renderer::index::format_32> current_index(
		indices.data());

	sge::renderer::size_type current_index_begin =
		0u;

	sge::model::obj::material_to_face_sequence const &current_parts(
		_prototype.parts());

	for(
		sge::model::obj::material_to_face_sequence::const_iterator current_part =
			current_parts.begin();
		current_part != current_parts.end();
		++current_part)
	{
		sge::model::obj::face_sequence const &current_face_sequence(
			current_part->second);

		for(
			sge::model::obj::face_sequence::const_iterator current_face =
				current_face_sequence.begin();
			current_face != current_face_sequence.end();
			++current_face)
		{
			for(
				sge::model::obj::face::const_iterator current_face_index =
					current_face->begin();
				current_face_index != current_face->end();
				++current_face_index)
			{
				(*current_index++).set(
					static_cast<sge::renderer::index::i32>(
						*current_face_index));
			}
		}

		parts_.insert(
			std::make_pair(
				sge::scenic::scene::identifier(
					current_part->first.get()),
				sge::scenic::index_buffer_range(
					sge::renderer::first_index(
						current_index_begin),
					sge::renderer::index_count(
						current_face_sequence.size()*3u))));

		current_index_begin +=
			current_face_sequence.size() * 3u;
	}
}
