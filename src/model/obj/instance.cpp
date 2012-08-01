#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/prototype.hpp>
#include <sge/model/obj/vf/format.hpp>
#include <sge/model/obj/vf/format_part.hpp>
#include <sge/model/obj/vf/normal.hpp>
#include <sge/model/obj/vf/position.hpp>
#include <sge/model/obj/vf/texcoord.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>


sge::model::obj::instance::instance(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration &_vertex_declaration,
	sge::model::obj::prototype const &_prototype)
:
	vertex_buffer_(
		_renderer.create_vertex_buffer(
			_vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index
			<
				sge::model::obj::vf::format,
				sge::model::obj::vf::format_part
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
sge::model::obj::instance::vertex_buffer()
{
	return
		*vertex_buffer_;
}

sge::renderer::index_buffer &
sge::model::obj::instance::index_buffer()
{
	return
		*index_buffer_;
}

sge::model::obj::material_to_index_buffer_range const &
sge::model::obj::instance::parts()
{
	return
		parts_;
}

sge::model::obj::box const &
sge::model::obj::instance::bounding_box() const
{
	return
		bounding_box_;
}

sge::model::obj::instance::~instance()
{
}

void
sge::model::obj::instance::fill_vertex_buffer(
	sge::model::obj::prototype const &_prototype)
{
	sge::renderer::scoped_vertex_lock const vblock(
		*vertex_buffer_,
		sge::renderer::lock_mode::writeonly);

	typedef
	sge::renderer::vf::view<sge::model::obj::vf::format_part>
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
		(*current_vertex).set<sge::model::obj::vf::position>(
			vertex_coordinates[
				current_face_vertex->vertex_coordinate_index().get()]);

		(*current_vertex).set<sge::model::obj::vf::texcoord>(
			texture_coordinates[
				current_face_vertex->texture_coordinate_index().get()]);

		(*current_vertex++).set<sge::model::obj::vf::normal>(
			normals[
				current_face_vertex->normal_index().get()]);
	}
}

void
sge::model::obj::instance::fill_index_buffer(
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

	for(
		sge::model::obj::material_to_face_sequence::const_iterator it =
			_prototype.parts().begin();
		it != _prototype.parts().end();
		++it)
	{
		for(
			sge::model::obj::face_sequence::const_iterator current_face =
				it->second.begin();
			current_face != it->second.end();
			++it)
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
				it->first,
				sge::model::obj::index_buffer_range(
					sge::renderer::first_index(
						current_index_begin),
					sge::renderer::index_count(
						it->second.size()))));

		current_index_begin +=
			it->second.size();
	}
}
