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


#include <sge/renderer/default_material.hpp>
#include <sge/renderer/material.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/scenic/render_queue/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{
template<typename StateSequence>
void
change_context_state(
	StateSequence &_states,
	typename StateSequence::value_type _state_ptr,
	sge::scenic::render_queue::index_type &_current_state)
{
	typename StateSequence::const_iterator it =
		std::find(
			_states.begin(),
			_states.end(),
			_state_ptr);

	if(it == _states.end())
	{
		_states.push_back(
			_state_ptr);

		it =
			boost::prior(
				_states.end());
	}

	typename StateSequence::const_iterator begin(
		_states.begin());

	_current_state =
		static_cast<
			sge::scenic::render_queue::index_type
		>(
			std::distance(
				begin,
				it));
}
}

sge::scenic::render_queue::object::object()
:
	materials_(),
	vertex_buffers_(),
	textures_(),
	meshes_(),
	current_material_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1)),
	current_vertex_buffer_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1)),
	current_texture_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1))
{
}

void
sge::scenic::render_queue::object::current_material(
	sge::renderer::material const &_material)
{
	change_context_state(
		materials_,
		&_material,
		current_material_);
}

void
sge::scenic::render_queue::object::current_vertex_buffer(
	sge::renderer::vertex_buffer &_vertex_buffer)
{
	change_context_state(
		vertex_buffers_,
		&_vertex_buffer,
		current_vertex_buffer_);
}

void
sge::scenic::render_queue::object::current_texture(
	fcppt::optional<sge::renderer::texture::planar &> _texture)
{
	if(_texture)
		change_context_state(
			textures_,
			&(*_texture),
			current_texture_);
	else
		change_context_state(
			textures_,
			0,
			current_texture_);
}

void
sge::scenic::render_queue::object::add_mesh(
	sge::renderer::matrix4 const &_modelview,
	sge::renderer::index_buffer &_index_buffer,
	sge::model::obj::index_buffer_range const &_index_buffer_range)
{
	meshes_.push_back(
		sge::scenic::render_queue::mesh(
			current_material_,
			current_vertex_buffer_,
			current_texture_,
			_modelview,
			_index_buffer,
			_index_buffer_range));
}

sge::scenic::render_queue::state_change_count const
sge::scenic::render_queue::object::render(
	sge::renderer::context::object &_context)
{
	std::sort(
		meshes_.begin(),
		meshes_.end());

	index_type const invalid_index =
		static_cast<index_type>(
			-1);

	index_type
		current_render_material =
			invalid_index,
		current_render_vertex_buffer =
			invalid_index,
		current_render_texture =
			invalid_index;

	sge::scenic::render_queue::state_change_count state_changes(
		0u);

	for(
		mesh_sequence::const_iterator current_mesh =
			meshes_.begin();
		current_mesh != meshes_.end();
		++current_mesh)
	{
		if(current_mesh->material() != current_render_material)
		{
			state_changes++;

			_context.material(
				*materials_[
					static_cast<material_sequence::size_type>(
						current_mesh->material())]);

			current_render_material =
				current_mesh->material();
		}

		if(current_mesh->vertex_buffer() != current_render_vertex_buffer)
		{
			state_changes++;

			if(current_render_vertex_buffer != invalid_index)
				_context.deactivate_vertex_buffer(
					*vertex_buffers_[
						static_cast<vertex_buffer_sequence::size_type>(
							current_render_vertex_buffer)]);

			_context.activate_vertex_buffer(
				*vertex_buffers_[
					static_cast<vertex_buffer_sequence::size_type>(
						current_mesh->vertex_buffer())]);

			current_render_vertex_buffer =
				current_mesh->vertex_buffer();
		}

		if(current_mesh->texture() != current_render_texture)
		{
			state_changes++;

			if(current_mesh->texture() == invalid_index || !textures_[static_cast<texture_sequence::size_type>(current_mesh->texture())])
				_context.texture(
					sge::renderer::texture::const_optional_base_ref(),
					sge::renderer::texture::stage(
						0u));
			else
				_context.texture(
					sge::renderer::texture::const_optional_base_ref(
						*textures_[
							static_cast<texture_sequence::size_type>(
								current_mesh->texture())]),
					sge::renderer::texture::stage(
						0u));

			current_render_texture =
				current_mesh->texture();
		}

		state_changes++;
		_context.transform(
			sge::renderer::matrix_mode::world,
				current_mesh->modelview());

		_context.render_indexed(
			current_mesh->index_buffer(),
			sge::renderer::first_vertex(
				0u),
			sge::renderer::vertex_count(
				vertex_buffers_[
					static_cast<vertex_buffer_sequence::size_type>(
						current_render_vertex_buffer)]->size()),
			sge::renderer::primitive_type::triangle_list,
			current_mesh->index_buffer_range().first_index(),
			current_mesh->index_buffer_range().index_count());
	}

	_context.deactivate_vertex_buffer(
		*vertex_buffers_[
			static_cast<vertex_buffer_sequence::size_type>(
				current_render_vertex_buffer)]);

	_context.texture(
		sge::renderer::texture::const_optional_base_ref(),
		sge::renderer::texture::stage(
			0u));

	_context.material(
		sge::renderer::default_material());

	return
		state_changes;
}

sge::scenic::render_queue::object::~object()
{
}
