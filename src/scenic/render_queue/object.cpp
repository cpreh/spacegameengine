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


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/transform_matrix_type.hpp>
#include <sge/scenic/render_queue/object.hpp>
#include <sge/scenic/scene/material/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{
template<typename StateSequence>
void
change_context_state(
	StateSequence &_states,
	typename StateSequence::value_type _state,
	sge::scenic::render_queue::index_type &_current_state)
{
	typename StateSequence::const_iterator it =
		std::find(
			_states.begin(),
			_states.end(),
			_state);

	if(it == _states.end())
	{
		_states.push_back(
			_state);

		it =
			std::prev(
				_states.end());
	}

	typename StateSequence::const_iterator begin(
		_states.begin());

	_current_state =
		static_cast<sge::scenic::render_queue::index_type>(
			std::distance(
				begin,
				it));
}
}

sge::scenic::render_queue::object::object(
	sge::scenic::texture_manager &_texture_manager)
:
	texture_manager_(
		_texture_manager),
	materials_(),
	vertex_buffers_(),
	meshes_(),
	current_material_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1)),
	current_vertex_buffer_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1))
{
}

void
sge::scenic::render_queue::object::current_material(
	sge::scenic::scene::material::object const &_material)
{
	sge::scenic::render_context::material::object const renderable_material(
		sge::scenic::render_context::diffuse_color(
			_material.diffuse_color().get()),
		sge::scenic::render_context::ambient_color(
			_material.ambient_color().get()),
		sge::scenic::render_context::specular_color(
			_material.specular_color().get()),
		sge::scenic::render_context::emissive_color(
			_material.emissive_color().get()),
		sge::scenic::render_context::material::shininess(
			_material.shininess().get()),
		_material.diffuse_texture().get().empty()
		?
			sge::scenic::render_context::material::diffuse_texture()
		:
			sge::scenic::render_context::material::diffuse_texture(
				texture_manager_.texture_for_path(
					_material.diffuse_texture().get())),
		_material.specular_texture().get().empty()
		?
			sge::scenic::render_context::material::specular_texture()
		:
			sge::scenic::render_context::material::specular_texture(
				texture_manager_.texture_for_path(
					_material.specular_texture().get())));

	change_context_state(
		materials_,
		renderable_material,
		current_material_);
}

void
sge::scenic::render_queue::object::current_vertex_buffer(
	sge::renderer::vertex::buffer &_vertex_buffer)
{
	change_context_state(
		vertex_buffers_,
		&_vertex_buffer,
		current_vertex_buffer_);
}

void
sge::scenic::render_queue::object::add_mesh(
	sge::renderer::matrix4 const &_modelview,
	sge::renderer::index::buffer &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
{
	meshes_.push_back(
		sge::scenic::render_queue::mesh(
			current_material_,
			current_vertex_buffer_,
			_modelview,
			_index_buffer,
			_index_buffer_range));
}

sge::scenic::render_queue::state_change_count
sge::scenic::render_queue::object::render(
	sge::scenic::render_context::base &_context)
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
				materials_[
					static_cast<material_sequence::size_type>(
						current_mesh->material())]);

			current_render_material =
				current_mesh->material();
		}

		if(current_mesh->vertex_buffer() != current_render_vertex_buffer)
		{
			state_changes++;

			_context.vertex_buffer(
				*vertex_buffers_[
					static_cast<vertex_buffer_sequence::size_type>(
						current_mesh->vertex_buffer())]);

			current_render_vertex_buffer =
				current_mesh->vertex_buffer();
		}

		state_changes++;
		_context.transform(
			sge::scenic::render_context::transform_matrix_type::world,
			current_mesh->modelview());

		_context.render(
			current_mesh->index_buffer(),
			current_mesh->index_buffer_range());
	}

	return
		state_changes;
}

sge::scenic::render_queue::object::~object()
{
}
